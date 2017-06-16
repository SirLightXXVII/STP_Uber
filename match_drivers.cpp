#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <chrono>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using namespace std::chrono;

double dist(double x1, double y1, double x2, double y2){
	double res = (x1-x2)*(x1-x2);
	res+=(y1-y2)*(y1-y2);
	return res;
}

int main(int, char**) {
    	mongocxx::instance inst{};
    	mongocxx::client conn{mongocxx::uri{}};

    	bsoncxx::builder::stream::document doc{};

    	auto order_coll = conn["newmydb"]["orders"];
        auto driver_coll = conn["newmydb"]["drivers"];

    	auto unfinished_orders =
       	order_coll.find(document{} << "AssignedTo" << open_document << "$exists" << false << close_document << finalize);

	auto now = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
	for (auto it = unfinished_orders.begin(); it!= unfinished_orders.end(); it++) {
		auto cur_order = *it;
	  	double cur_x = cur_order["PointA_Lat"].get_double(); double cur_y = cur_order["PointA_Lon"].get_double();
		
		auto free_drivers = driver_coll.find(document{} << "$or" << open_document << "AvailibleAt" << open_document << "$exists" << false << close_document << close_document
							       << open_document << "AvailibleAt" << open_document << "$lt" << system_clock::now() << close_document << close_document << finalize);
		bsoncxx::document::view closest_driver; double min_dist = 180;
		for (auto jt = free_drivers.begin(); jt!=free_drivers.end(); jt++){
			auto cur_driver = *jt;
			double cdx = cur_driver["CurrentLatitute"].get_double(); double cdy = cur_driver["CurrentLongitude"].get_double();
			if (dist(cdx, cdy, cur_x, cur_y)<min_dist){
				min_dist = dist(cdx,cdy, cur_x, cur_y);
				closest_driver = cur_driver;
			}
		}
		if (abs(min_dist - 180)<1e-10) break;
		order_coll.update(document{} << "_id" << cur_order["_id"] << finalize, document{} << "$set" << open_document << "AssignedTo" << cur_driver["_id"] << close_document << finalize);
		auto free_at = system_clock::now() + hours(2);
		driver_coll.update(document{} << "_id" << closest_driver["_id"] << finalize, document{} << "$set" << open_document << "AvailibleAt" << free_at << close_document << finalize);
	}



}

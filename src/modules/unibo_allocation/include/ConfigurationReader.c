#include <stdio.h>
//#include <algorithm>
//
//#include "ConfigurationReader.h"
#include "mr_config_struct.h"
//#include "pugixml.hpp"
////
//using namespace std;

struct mr_config_struct ConfigurationReader(int change_flag,int on_flag[6])//void main()//
{
	FILE * fp=fopen("unibo_configuration/unibo_configuration.txt","r");
	if(fp==NULL){
		warnx("error!!!");
	}else{
		warnx("ok");
	}
//    int index;
//    const int rotors_number=6;
//    char* module_name=new char();
//    pugi::xml_document doc;
//    pugi::xml_node vehicle;
//    pugi::xml_node modules_set;
//    pugi::xml_node module;
//    pugi::xml_parse_result result=doc.load_file("multirotor_config_data.xml");
//    if(result.status==1){
//        pugi::xml_node decl=doc.prepend_child(pugi::node_declaration);
//        decl.append_attribute("version")="1.0";
//        decl.append_attribute("encoding")="UTF-8";
//        decl.append_attribute("standalone")="no";
//        vehicle=doc.append_child();
//        vehicle.set_name("multirotor_configuration");
//        modules_set=vehicle.append_child();
//        modules_set.set_name("active_modules");
//        for(int index=1;index<=rotors_number;index++){
//            module=modules_set.append_child();
//            sprintf(module_name,"module_%d",index);
//            module.set_name(module_name);
//            module.append_attribute("r")="200";
//            module.append_attribute("h")="50";
//            module.append_attribute("psi")=std::to_string((long double)(90*(index-1))).c_str();
//            module.append_attribute("mass")="100";
//            module.append_attribute("spin")="1";
//            module.append_attribute("Kt")="345";
//            module.append_attribute("Kq")="1768";
//            module.append_attribute("operating")="1";
//        }
//        modules_set=vehicle.append_child();
//        modules_set.set_name("passive_modules");
//        for(int index=1;index<=2;index++){
//            module=modules_set.append_child();
//            sprintf(module_name,"module_%d",index);
//            module.set_name(module_name);
//            module.append_attribute("r")="0";
//            module.append_attribute("h")=std::to_string((long double)(50*(index-1))).c_str();
//            module.append_attribute("mass")=std::to_string((long double)(100-(50*(index-1)))).c_str();
//        }
//        doc.save_file("multirotor_config_data.xml");
//        printf("\nWARNING: multirotor configuration file missing; \"multirotor config data.xml\" file generated\n");
//    }
//    if(change_flag){
//        vehicle=doc.child("multirotor_configuration");
//        modules_set=vehicle.child("active_modules");
//        index=0;
//        for(pugi::xml_node_iterator module_iterator=modules_set.begin();module_iterator!= modules_set.end();++module_iterator)
//        {
//            module_iterator->attribute("operating").set_value(on_flag[index]);
//            index++;
//        }
//        doc.save_file("multirotor_config_data.xml");
//    }
//    vehicle=doc.child("multirotor_configuration");
//    modules_set=vehicle.child("active_modules");
    struct mr_config_struct current_config;
//    index=0;
//    for(module=modules_set.first_child();module;module=module.next_sibling())
//    {
//        if(atoi(module.attribute("operating").value())){
//            current_config.radius[index]=atoi(module.attribute("r").value());
//            current_config.height[index]=atoi(module.attribute("h").value());
//            current_config.azimut[index]=atoi(module.attribute("psi").value());
//            current_config.mass[index]=atoi(module.attribute("mass").value());
//            current_config.direction[index]=atoi(module.attribute("spin").value());
//            current_config.operating[index]=atoi(module.attribute("operating").value());
//            current_config.thrust[index]=atoi(module.attribute("Kt").value());
//            current_config.torque[index]=atoi(module.attribute("Kq").value());
//        }else{
//            current_config.radius[index]=0;
//            current_config.height[index]=0;
//            current_config.azimut[index]=0;
//            current_config.mass[index]=0;
//            current_config.direction[index]=0;
//            current_config.operating[index]=0;
//            current_config.thrust[index]=0;
//            current_config.torque[index]=0;
//        }
//        index++;
//    }
    return current_config;
}

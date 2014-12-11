#include <stdio.h>
#include <math.h>

#include "mr_config_struct.h"

struct mr_config_struct ConfigurationReader(int change_flag,int on_flag[6])//void main()//
{
	int str_len=100*8;
	FILE *cf_file_hnd=fopen("/fs/microsd/quadrotor_configuration.qcf","r");
	struct mr_config_struct current_config;
	if(cf_file_hnd!=NULL){
		char cf_str[str_len];
		do{
			fgets(cf_str,str_len,cf_file_hnd);
		}while(strstr(cf_str,"<TAB")==NULL);
		unsigned int module_num;
		sscanf(cf_str,"<TAB,%u,%*u>",&module_num);
		current_config.rotors_number=module_num;
		unsigned int module_ind;
		unsigned int module_r;
		unsigned int module_diam;
		int module_dir;
		int module_thrust;
		int module_torque;
		for(int loop_ind=0;loop_ind<module_num;loop_ind++){
			do{
				fgets(cf_str,str_len,cf_file_hnd);
			}while(strstr(cf_str,"<ROW")==NULL);
			sscanf(cf_str,"<ROW,%u,%u,%u,%d,%d,%d>",
					&module_ind,&module_r,&module_diam,
					&module_dir,&module_thrust,&module_torque);
			current_config.radius[module_ind-1]=module_r;
			current_config.diameter[module_ind-1]=module_diam;
			current_config.direction[module_ind-1]=module_dir;
			current_config.thrust[module_ind-1]=1.225f*(float)pow(module_diam/1.0e3,4)*(module_thrust/(float)1e3);
			current_config.torque[module_ind-1]=1.225f*(float)pow(module_diam/1.0e3,5)*(module_torque/(float)1e3);
		}
		fclose(cf_file_hnd);
	}else{
		warnx("error!!!");
	}
    return current_config;
}

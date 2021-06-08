/****************************************************************************
 *
 *   Copyright (c) 2018-2021 Jaeyoung Lim. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * @brief Geometric Controller Node
 *
 * Geometric controller ROS Node Implementation
 *
 * @author Jaeyoung Lim <jalim@ethz.ch>
 */

#include "geometric_controller/geometric_controller.h"
#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
  ros::init(argc, argv, "geometric_controller");
  ros::NodeHandle nh("");
  ros::NodeHandle nh_private("~");


  std::fstream infile;
  infile.open("/home/chasing/Downloads/mavros_controller/parameter.txt",std::ios::in);
  if(!infile.is_open()){
      ROS_ERROR("error for load the parameters.txt....");
      exit(EXIT_FAILURE);
  }else{
        for(uint8_t i=0;i<MINISNAP_ROW;i++){
            for(uint8_t j=0;j<MINISNAP_COL;j++){
                infile >> parameter(i,j);
            }
        }
  }
  infile.close();
  for(uint8_t i=0;i<MINISNAP_ROW;i++){
      for(uint8_t j=0;j<MINISNAP_COL;j++){
            std::cout<< parameter(i,j)<<"\t";
      }
      std::cout<<std::endl;
  }

  std::fstream timefiles;
  timefiles.open("/home/chasing/Downloads/mavros_controller/save_timer.txt",std::ios::in);
  if(!timefiles.is_open()){
      ROS_ERROR("error for load the timer.txt...");
      exit(EXIT_FAILURE);
  }else{
    for(uint8_t i=0;i<MINISNAP_ROW;i++){
      timefiles >> poly_timer(i);
    }
    ROS_INFO("reading the timer data successfully...");
  }
  timefiles.close();


  geometricCtrl* geometricController = new geometricCtrl(nh, nh_private);

  // dynamic_reconfigure::Server<geometric_controller::GeometricControllerConfig> srv;
  // dynamic_reconfigure::Server<geometric_controller::GeometricControllerConfig>::CallbackType f;
  // f = boost::bind(&geometricCtrl::dynamicReconfigureCallback, geometricController, _1, _2);
  // srv.setCallback(f);

  ros::spin();
  return 0;
}

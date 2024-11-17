#ifndef __EV3DEV__PORTS__H
#define __EV3DEV__PORTS__H
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>

class port_not_found {
private:
  std::string message;

public:
  port_not_found(std::string messages) { message = messages; }
  std::string what() { return message; }
};

std::string get_type_for_sensor(int port) {
  std::string target_address = "ev3-ports:in" + std::to_string(port);
  std::string sensor_dir = "/sys/class/lego-sensor";
  DIR *dir = opendir(sensor_dir.c_str());
  if (!dir) {
    perror("opendir failed");
    throw std::runtime_error("failed to open directory");
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string sensor_name = entry->d_name;

    if (sensor_name == "." || sensor_name == "..") {
      continue;
    }

    std::string address_file = sensor_dir + "/" + sensor_name + "/address";
    std::ifstream address_stream(address_file);
    if (!address_stream.is_open()) {
      continue;
    }

    std::string address;
    std::getline(address_stream, address);

    if (address == target_address) {
      std::string driver_file = sensor_dir + "/" + sensor_name + "/driver_name";
      std::ifstream driver_stream(driver_file);
      if (!driver_stream.is_open()) {
        closedir(dir);
        return "";
      }

      std::string driver_name;
      std::getline(driver_stream, driver_name);
      closedir(dir);
      return driver_name;
    }
  }

  closedir(dir);
  throw port_not_found(std::to_string(port));
}
std::string get_directory_for_sensor(int port) {
  std::string target_address = "ev3-ports:in" + std::to_string(port);
  std::string sensor_dir = "/sys/class/lego-sensor";
  DIR *dir = opendir(sensor_dir.c_str());
  if (!dir) {
    perror("opendir failed");
    throw std::runtime_error("failed to open directory");
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string sensor_name = entry->d_name;

    if (sensor_name == "." || sensor_name == "..") {
      continue;
    }

    std::string address_file = sensor_dir + "/" + sensor_name + "/address";
    std::ifstream address_stream(address_file);
    if (!address_stream.is_open()) {
      continue;
    }

    std::string address;
    std::getline(address_stream, address);

    if (address == target_address) {
      return sensor_dir + "/" + sensor_name;
    }
  }

  closedir(dir);
  throw port_not_found(std::to_string(port));
}

std::string get_type_for_tacho_motor(char port) {
  std::string target_address = "ev3-ports:out";
  target_address += port;
  std::string motor_dir = "/sys/class/tacho-motor";
  DIR *dir = opendir(motor_dir.c_str());
  if (!dir) {
    perror("opendir failed");
    throw std::runtime_error("failed to open directory");
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string motor_name = entry->d_name;
    if (motor_name == "." || motor_name == "..")
      continue;
    std::string address_file = motor_dir + "/" + motor_name + "/address";
    {
      std::ifstream address_stream(address_file);
      if (!address_stream.is_open())
        continue;
      std::string address;
      std::getline(address_stream, address);
      if (address == target_address) {
        std::string driver_file = motor_dir + "/" + motor_name + "/driver_name";
        {
          std::ifstream driver_stream(driver_file);
          if (!driver_stream.is_open()) {
            closedir(dir);
            return "";
          }
          std::string driver_name;
          std::getline(driver_stream, driver_name);
          closedir(dir);
          return driver_name;
        }
      }
    }
  }
  closedir(dir);
  throw port_not_found(std::to_string(port));
}
std::string get_directory_for_tacho_motor(char port) {
  std::string target_address = "ev3-ports:out";
  target_address += port;
  std::string motor_dir = "/sys/class/tacho-motor";
  DIR *dir = opendir(motor_dir.c_str());
  if (!dir) {
    perror("opendir failed");
    throw std::runtime_error("failed to open directory");
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string motor_name = entry->d_name;
    if (motor_name == "." || motor_name == "..")
      continue;
    std::string address_file = motor_dir + "/" + motor_name + "/address";
    {
      std::ifstream address_stream(address_file);
      if (!address_stream.is_open())
        continue;
      std::string address;
      std::getline(address_stream, address);
      if (address == target_address) {
        return motor_dir + "/" + motor_name;
      }
    }
  }
  closedir(dir);
  throw port_not_found(std::to_string(port));
}
#endif

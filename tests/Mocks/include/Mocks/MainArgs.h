#pragma once

#include <memory>
#include <string>
#include <vector>

struct MainArgs
{
   std::vector<std::string> args;
   std::unique_ptr<char*[]> argv_;
   
   MainArgs() = default;

   MainArgs& operator()(const std::string& value)
   {
      args.push_back(value);
      return *this;
   }
   MainArgs& operator()(const std::string& option, const std::string& value)
   {
      args.push_back(option);
      args.push_back(value);
      return *this;
   }
   MainArgs& operator()(const std::string& option, int value)
   {
      args.push_back(option);
      args.push_back(std::to_string(value));
      return *this;
   }
   int argc()
   {
      return args.size();
   }
   char** argv()
   {
      argv_.reset(new char*[args.size()+1]);
      int i=0;

      for (; i<args.size(); ++i)
      {
         argv_[i] = &args[i][0];
      }

      argv_[i] = nullptr;
      return &argv_[0];
   }
};


#pragma once
// 
// File:         MyMessage
// Description:  Used for testing the PNF Framework 
//

#include "Framework/PNFMessageAlt.h"
#include "Framework/PNFMessageBase.h"

//
// Dependent data structures
//

#include <memory>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


namespace testing
{

   // 
   // Message Contract Declaration
   //
   class MyMessage : public pnf::PNFMessageBase
   {
      /*
       * MyMessage
       *
       * Description: Test Message
       *
       */
      public:
         //
         // Message Data Declaration
         //
         // Recommend using nounds for names
         string name = "Bert from accounting";

         //
         // CTOR/DTOR Declaration
         //
         MyMessage();
         MyMessage(::contract::IContext& context, const std::string& contextName, bool isMQTTSubscriber=true);
         virtual ~MyMessage();

         //
         // Object Copy Declaration
         //
         MyMessage(const MyMessage& other);
         MyMessage& operator=(const MyMessage& lhs);

         //
         // Printer Network Framework Declaration
         //
         bool isPNF();
         PNFMessageAltPtr pnf();
         bool isSubscription();
         void setCallback(std::function<void(const MyMessage&)> callback);

         //
         // Json File Serialization Declaration
         //
         PNFMessageSerialization serializer();

      private:
         PNFMessageAltPtr _pnf;

         void copy(const MyMessage& from);

      public:
         friend std::ostream& operator<<(std::ostream& out, const MyMessage& m);
   };

   //
   // Message Class Json Serialization Declaration
   //
   void to_json(json& j, const MyMessage& p);
   void from_json(const json& j, MyMessage& p);
}
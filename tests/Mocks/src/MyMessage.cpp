#include "Mocks/MyMessage.h"
#include "Framework/Time.h"
#include "MessageFramework/BoostOptionalJsonSerializer.h"
#include <ostream>

namespace testing
{
   // 
   // Dependent Class Implementation
   //

   // 
   // Message Contract Class Implementation
   //
   // 
   // Implementation Section for MyMessage
   //

   //
   // CTOR/DTOR Section
   //
   MyMessage::MyMessage(::contract::IContext& context, const std::string& contextName, bool isMQTTSubscriber) :
      _pnf(new ::contract::PNFMessageAlt<MyMessage>(*this, context, "MyMessage", contextName, isMQTTSubscriber))
   {
      context.context(contextName, _pnf);
   }
   MyMessage::MyMessage() :
      _pnf(new ::contract::PNFMessageAlt<MyMessage>(*this, "MyMessage"))
   {
   }
   MyMessage::~MyMessage()
   {
   }

   //
   // node Copy Section
   //
   MyMessage::MyMessage(const MyMessage& other)
   {
      copy(other);
   }
   MyMessage& MyMessage::operator=(const MyMessage& lhs)
   {
      copy(lhs);
      return *this;
   }
   void MyMessage::copy(const MyMessage& from)
   {
      name = from.name;
      pnf::PNFMessageBase::copy(from);
   }

   //
   // Printer Network Framework Section
   //
   bool MyMessage::isPNF()
   {
      return static_cast<bool>(_pnf);
   }
   PNFMessageAltPtr MyMessage::pnf()
   {
      return _pnf;
   }
   bool MyMessage::isSubscription()
   {
      return (isPNF() && pnf()->isSubscription());
   }
   void MyMessage::setCallback(std::function<void(const MyMessage&)> callback)
   {
      if (isPNF())
      {
         std::shared_ptr<::contract::PNFMessageAlt<MyMessage>> p = std::static_pointer_cast<::contract::PNFMessageAlt<MyMessage>>(_pnf);
         p->setCallback(callback);
      }
      else
      {
         LOG(WARNING) << "ERROR: MyMessage callback failed";
      }
   }

   //
   // Json File Serialization Section
   //
   PNFMessageSerialization MyMessage::serializer()
   {
      return _pnf;
   }

   //  
   // Default Stream Operator
   //  
   std::ostream& operator<<(std::ostream& out, const MyMessage& m)
   {   
      framework::Time time;
      out << "MyMessage|";
      out << time.diffTimepoints(m.receiveTimestamp, m.sendTimestamp);
      out << "|";
      out << time.timestamp(m.sendTimestamp);
      out << "|";
      out << time.timestamp(m.receiveTimestamp);
      return out;
   };  


   //
   // Json Implementation 
   //

   void to_json(json& j, const testing::MyMessage& p)
   {
      j = json{ {"name", p.name},};
   }
   void from_json(const json& j, testing::MyMessage& p)
   {
      j.at("name").get_to(p.name);
   }

} // namespace testing

#pragma once

#include "Framework/IPNFMessageAlt.h"
// #include "Framework/IPNFMessageAltProvidedRequired.h"

#include <any>
#include <fstream>
#include <memory>

namespace mocks
{

   // struct MockIMessageProvided : public contract::IMessageProvided
   // {
   //    std::string getTopic_return;

   //    const std::string& getTopic() const override
   //    {
   //       return getTopic_return;
   //    }

   //    bool isSubscription_return { true };
   //    bool isSubscription() override
   //    {
   //       return isSubscription_return;
   //    }
   //    MessageRequiredPtr setContext_param1;
   //    void setContext(MessageRequiredPtr param1) override
   //    {
   //       setContext_param1 = param1;
   //    }

   // };

   struct MockIMessageRequired : public contract::IMessageRequired
   {
      virtual ~MockIMessageRequired() {}

      bool dispatch_isCalled { false };
      unsigned dispatch_callCount { 0 };

      void dispatch(const std::string& topic, const std::string& payload) override
      {
         dispatch_isCalled = true;
         ++dispatch_callCount;
      }

      bool publish_isCalled { false };
      unsigned publish_callCount { 0 };
      std::string publish_param_1;
      std::string publish_param_2;

      void publish(const std::string& topic, const std::string& payload) override
      {
         publish_isCalled = true;
         ++publish_callCount;
         publish_param_1 = topic;
         publish_param_2 = payload;
      }
   };

   struct MockIContext : public contract::IContext
   {
      MockIContext() :
         context_ptr(new MockIMessageRequired())
      {}
      virtual ~MockIContext() {}

      MessageRequiredPtr context_ptr;

      bool context_isCalled { false };
      unsigned context_callCount { 0 };
      std::any context_param_1;
      PNFMessageAltPtr context_messages;

      void context(const std::string& topic, PNFMessageAltPtr message, bool isInternalRoute=true) override
      {
         context_isCalled = true;
         ++context_callCount;
         context_param_1 = topic;
         context_messages = message;

         message->setContext(context_ptr);
      }

      std::shared_ptr<MockIMessageRequired> getThreadContext()
      {
         return std::static_pointer_cast<MockIMessageRequired>(context_ptr);
      }
   };

} // namespace mocks

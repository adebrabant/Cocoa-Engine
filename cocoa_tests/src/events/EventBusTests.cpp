#include <events/EventBus.hpp>
#include <gtest/gtest.h>

namespace cocoa_tests::events
{
	struct MockTestEvent
	{
		float Value;
	};

	TEST(EventBusTests, Subscribe_ShouldAddSubscriber_WhenValidSubscriberProvided)
	{
		cocoa::events::EventBus eventBus;

		auto eventToken = eventBus.subscribe<MockTestEvent>([](const MockTestEvent&){ });

		EXPECT_TRUE(eventBus.hasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, Subscribe_ShouldAllowMultipleSubscriptions_UsingSameHandler)
	{
		cocoa::events::EventBus eventBus;
		int callCount = 0;

		auto handler = [&](const MockTestEvent&) { ++callCount; };

		eventBus.subscribe<MockTestEvent>(handler);
		eventBus.subscribe<MockTestEvent>(handler);

		eventBus.publish(MockTestEvent{});

		EXPECT_EQ(callCount, 2);
	}

	TEST(EventBusTests, Unsubscribe_ShouldRemoveSubscriber_WhenValidSubscriberProvided)
	{
		cocoa::events::EventBus eventBus;

		auto eventToken = eventBus.subscribe<MockTestEvent>([](const MockTestEvent&){ });
		eventBus.unsubscribe<MockTestEvent>(eventToken);

		EXPECT_FALSE(eventBus.hasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, Publish_ShouldNotifyAllSubscribers_WhenEventIsPublished)
	{
		cocoa::events::EventBus eventBus;
		bool isNotified = false;
		auto eventToken = eventBus.subscribe<MockTestEvent>(
			[&isNotified](const MockTestEvent&)
			{
				isNotified = true;
			}
		);

		eventBus.publish(MockTestEvent{ 200.f });

		EXPECT_TRUE(isNotified);
	}

	TEST(EventBusTests, Publish_ShouldNotifyAllSubscribers_WhenMultipleSubsribersExist)
	{
		cocoa::events::EventBus eventBus;
		int notificationCount = 0;

		eventBus.subscribe<MockTestEvent>([&notificationCount](const MockTestEvent&) { ++notificationCount; });
		eventBus.subscribe<MockTestEvent>([&notificationCount](const MockTestEvent&) { ++notificationCount; });

		eventBus.publish(MockTestEvent{ });

		EXPECT_EQ(notificationCount, 2);
	}

	TEST(EventBusTests, Publish_ShouldNotNotifySubscriber_AfterUnsubscribe)
	{
		cocoa::events::EventBus eventBus;
		bool isNotified = false;
		auto eventToken = eventBus.subscribe<MockTestEvent>(
			[&isNotified](const MockTestEvent&)
			{
				isNotified = true;
			}
		);

		eventBus.unsubscribe<MockTestEvent>(eventToken);
		eventBus.publish(MockTestEvent{ });

		EXPECT_FALSE(isNotified);
	}

	TEST(EventBusTests, Publish_ShouldDoNothing_WhenNoSubcribersExist)
	{
		cocoa::events::EventBus eventBus;

		EXPECT_NO_THROW(eventBus.publish(MockTestEvent{ 100.f }));
		EXPECT_NO_THROW(eventBus.publish(MockTestEvent{ 100.f }));
	}

	TEST(EventBusTests, Publish_ShouldPassCorrectEventData_ToSubscribers)
	{
		cocoa::events::EventBus eventBus;
		float receivedValue = 0.f;

		eventBus.subscribe<MockTestEvent>(
			[&](const MockTestEvent& evt) {
				receivedValue = evt.Value;
			}
		);

		eventBus.publish(MockTestEvent{ 42.0f });

		EXPECT_FLOAT_EQ(receivedValue, 42.0f);
	}

	TEST(EventBusTests, HasSubscriber_ShouldReturnTrue_WhenSubcribersExist)
	{
		cocoa::events::EventBus eventBus;
		auto eventToken = eventBus.subscribe<MockTestEvent>([](const MockTestEvent&) {});

		EXPECT_TRUE(eventBus.hasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, HasSubscriber_ShouldReturnFalse_WhenSubcribersDoNotExist)
	{
		cocoa::events::EventBus eventBus;
		auto eventToken = 1;

		EXPECT_FALSE(eventBus.hasSubscriber<MockTestEvent>(eventToken));
	}
}

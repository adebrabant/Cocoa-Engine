#include <Events/EventBus.hpp>
#include <gtest/gtest.h>

namespace Cocoa::Events::Tests
{
	struct MockTestEvent
	{
		float Value;
	};

	TEST(EventBusTests, Subscribe_ShouldAddSubscriber_WhenValidSubscriberProvided)
	{
		Cocoa::Events::EventBus eventBus;

		auto eventToken = eventBus.Subscribe<MockTestEvent>([](const MockTestEvent&){ });

		EXPECT_TRUE(eventBus.HasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, Subscribe_ShouldAllowMultipleSubscriptions_UsingSameHandler)
	{
		Cocoa::Events::EventBus eventBus;
		int callCount = 0;

		auto handler = [&](const MockTestEvent&) { ++callCount; };

		eventBus.Subscribe<MockTestEvent>(handler);
		eventBus.Subscribe<MockTestEvent>(handler);

		eventBus.Publish(MockTestEvent{});

		EXPECT_EQ(callCount, 2);
	}

	TEST(EventBusTests, Unsubscribe_ShouldRemoveSubscriber_WhenValidSubscriberProvided)
	{
		Cocoa::Events::EventBus eventBus;

		auto eventToken = eventBus.Subscribe<MockTestEvent>([](const MockTestEvent&){ });
		eventBus.Unsubscribe<MockTestEvent>(eventToken);

		EXPECT_FALSE(eventBus.HasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, Publish_ShouldNotifyAllSubscribers_WhenEventIsPublished)
	{
		Cocoa::Events::EventBus eventBus;
		bool isNotified = false;
		auto eventToken = eventBus.Subscribe<MockTestEvent>(
			[&isNotified](const MockTestEvent&)
			{
				isNotified = true;
			}
		);

		eventBus.Publish(MockTestEvent{ 200.f });

		EXPECT_TRUE(isNotified);
	}

	TEST(EventBusTests, Publish_ShouldNotifyAllSubscribers_WhenMultipleSubsribersExist)
	{
		Cocoa::Events::EventBus eventBus;
		int notificationCount = 0;

		eventBus.Subscribe<MockTestEvent>([&notificationCount](const MockTestEvent&) { ++notificationCount; });
		eventBus.Subscribe<MockTestEvent>([&notificationCount](const MockTestEvent&) { ++notificationCount; });

		eventBus.Publish(MockTestEvent{ });

		EXPECT_EQ(notificationCount, 2);
	}

	TEST(EventBusTests, Publish_ShouldNotNotifySubscriber_AfterUnsubscribe)
	{
		Cocoa::Events::EventBus eventBus;
		bool isNotified = false;
		auto eventToken = eventBus.Subscribe<MockTestEvent>(
			[&isNotified](const MockTestEvent&)
			{
				isNotified = true;
			}
		);

		eventBus.Unsubscribe<MockTestEvent>(eventToken);
		eventBus.Publish(MockTestEvent{ });

		EXPECT_FALSE(isNotified);
	}

	TEST(EventBusTests, Publish_ShouldDoNothing_WhenNoSubcribersExist)
	{
		Cocoa::Events::EventBus eventBus;

		EXPECT_NO_THROW(eventBus.Publish(MockTestEvent{ 100.f }));
		EXPECT_NO_THROW(eventBus.Publish(MockTestEvent{ 100.f }));
	}

	TEST(EventBusTests, Publish_ShouldPassCorrectEventData_ToSubscribers)
	{
		Cocoa::Events::EventBus eventBus;
		float receivedValue = 0.f;

		eventBus.Subscribe<MockTestEvent>(
			[&](const MockTestEvent& evt) {
				receivedValue = evt.Value;
			}
		);

		eventBus.Publish(MockTestEvent{ 42.0f });

		EXPECT_FLOAT_EQ(receivedValue, 42.0f);
	}

	TEST(EventBusTests, HasSubscriber_ShouldReturnTrue_WhenSubcribersExist)
	{
		Cocoa::Events::EventBus eventBus;
		auto eventToken = eventBus.Subscribe<MockTestEvent>([](const MockTestEvent&) {});

		EXPECT_TRUE(eventBus.HasSubscriber<MockTestEvent>(eventToken));
	}

	TEST(EventBusTests, HasSubscriber_ShouldReturnFalse_WhenSubcribersDoNotExist)
	{
		Cocoa::Events::EventBus eventBus;
		auto eventToken = 1;

		EXPECT_FALSE(eventBus.HasSubscriber<MockTestEvent>(eventToken));
	}
}
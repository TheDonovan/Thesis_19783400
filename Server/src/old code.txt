/*
 * Copyright (c) 2022 Circuit Dojo LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//INCLUDES
#include <stdio.h>
#include <zephyr/net/net_if.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(log_register, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/net/ethernet.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

//DEFINES
#define SLEEP_TIME_MS 100
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

#if IS_ENABLED(CONFIG_NET_L2_ETHERNET)
#include <zephyr/net/net_if.h>
#endif

//NETWORK CALLBACK SETUP
static struct net_mgmt_event_callback mgmt_cb;

static void start_dhcpv4_client(struct net_if *iface, void *user_data)
{
	ARG_UNUSED(user_data);

	net_dhcpv4_start(iface);
}

static void net_mgmt_handler(struct net_mgmt_event_callback *cb, uint32_t mgmt_event, struct net_if *iface)
{
    int i = 0;

    switch (mgmt_event)
    {
    case NET_EVENT_IPV4_ADDR_ADD:

        for(i=0;i<NET_IF_MAX_IPV4_ADDR;i++)
        {
            char buf[NET_IPV4_ADDR_LEN];

            if(iface->config.ip.ipv4->unicast[i].ipv4.addr_type != NET_ADDR_DHCP)
            {
                continue;
            }

            LOG_INF("   Address[%d]: %s", net_if_get_by_iface(iface),
			net_addr_ntop(AF_INET,
			    &iface->config.ip.ipv4->unicast[i].ipv4.address.in_addr,
						  buf, sizeof(buf)));
        }
        break;
    
    default:
        LOG_INF("NO IP ADDRESS...\n");
        break;
    }
}

void blink_led(void)
{
    //BLINKING LED CODE

    int ret;


    if(!gpio_is_ready_dt(&led))
    {
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    
    if(ret < 0)
    {
        return;
    }
    gpio_pin_set_dt(&led, 1);
    //gpio_pin_toggle_dt(&led);
    k_msleep(SLEEP_TIME_MS);
    gpio_pin_set_dt(&led, 0);
    k_msleep(SLEEP_TIME_MS);
    //gpio_pin_toggle_dt(&led);
}

int main(void)
{
    //BASED OFF: https://github.com/golioth/samples/tree/main/hello-ethernet
    if(IS_ENABLED(CONFIG_NET_L2_ETHERNET))
    {
        LOG_INF("STARTING DEVICE...\n");
        struct net_if *iface;
        iface = net_if_get_default();

        net_mgmt_init_event_callback(&mgmt_cb, net_mgmt_handler, NET_EVENT_IPV4_ADDR_ADD);
        net_mgmt_add_event_callback(&mgmt_cb);

        net_if_foreach(start_dhcpv4_client, NULL);
        //net_dhcpv4_start(iface);

        while(1)
        {
            if (net_if_is_carrier_ok(iface))
            {
                blink_led();
            }

            else
            {
                LOG_INF("Network down..\n");
            }
        }
        

    }
}

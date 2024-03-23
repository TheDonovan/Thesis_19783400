/*
 * Copyright (c) 2022 Circuit Dojo LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//INCLUDES
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(log_register, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

//DEFINES
//#define SPI_OP  SPI_OP_MODE_MASTER |SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD_SET(8) | SPI_LINES_SINGLE

#if IS_ENABLED(CONFIG_NET_L2_ETHERNET)
#include <zephyr/net/net_if.h>
#endif

int main(void)
{
    //BASED OFF: https://github.com/golioth/samples/tree/main/hello-ethernet
    if(IS_ENABLED(CONFIG_NET_L2_ETHERNET))
    {
        LOG_INF("Ethernet Available");
        struct net_if *iface;
        iface = net_if_get_default();
        net_dhcpv4_start(iface);
    }    

}

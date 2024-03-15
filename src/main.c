/*
 * Copyright (c) 2022 Circuit Dojo LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//INCLUDES
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

//DEFINES
//#define SPI_OP  SPI_OP_MODE_MASTER |SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD_SET(8) | SPI_LINES_SINGLE

int main(void)
{
/*
	//VARIABLES
	uint8_t my_buffer[4] = {0};
	struct spi_buf spi_buffer[1];
	spi_buffer[0].buf = my_buffer;
	spi_buffer[0].len = 4;
	const struct spi_buf_set rx_buff = { spi_buffer, 1};

	const struct spi_dt_spec lan9370_dev =
                SPI_DT_SPEC_GET(DT_NODELABEL(lan9370), SPI_OP, 0);

	ret = spi_read_dt(&lan9370_dev, &rx_buff);
	if (ret) { LOG_INF("spi_read status: %d", ret); }

	return(0);
*/
}

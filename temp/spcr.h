/*
 * spi.h
 *
 *  Created on: Aug 26, 2012
 *      Author: mrenouf
 */

#ifndef SPCR_H_
#define SPCR_H_

// Definitions for SPI clock settings (SPCR)

#define SPI_CLK_SCALE_2 (1 << SPI2X)
#define SPI_CLK_SCALE_4 (0)
#define SPI_CLK_SCALE_8 ((1 << SPR0) | (1 << SPI2X))
#define SPI_CLK_SCALE_16 (1 << SPR0)
#define SPI_CLK_SCALE_32 ((1 << SPR1) | (1 << SPI2X))
#define SPI_CLK_SCALE_64 (1 << SPR1)
#define SPI_CLK_SCALE_128 ((1 << SPR0) | (1 << SPI2X))

#define SPI_MSB_FIRST (0)
#define SPI_LSB_FIRST (1 << DORD)

#endif /* SPCR_H_ */

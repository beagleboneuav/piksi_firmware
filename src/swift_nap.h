/*
 * Copyright (C) 2011 Fergus Noble <fergusnoble@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SWIFTNAV_SWIFT_NAP_H
#define SWIFTNAV_SWIFT_NAP_H

#include <libopencm3/cm3/common.h>

#define SPI_ID_ACQ_INIT 0x00
#define SPI_ID_ACQ_LOAD_ENABLE 0x01
#define SPI_ID_ACQ_CORR 0x02

#define ACQ_N_TAPS 15
#define ACQ_CARRIER_PHASE_WIDTH 20

typedef struct {
  s32 I; s32 Q;
} corr_t;

void swift_nap_setup();
void swift_nap_reset();
void swift_nap_xfer(u8 spi_id, u8 n_bytes, u8 data_in[], u8 data_out[]);
void timing_strobe_setup();
u32 timing_count();
void timing_strobe(u32 falling_edge_count);
void acq_set_load_enable();
void acq_clear_load_enable();
u32 acq_init(u8 enabled, u8 svid, u16 code_phase, s16 carrier_freq);
void acq_disable();
//u32 unpack_22bits(u32 n, u8 A[]);
void acq_read_corr(corr_t corrs[]);

void do_one_acq(u8 svid, u16 code_phase, s16 carrier_freq, corr_t corrs[]);
void do_acq(u8 svid, u16 cp_min, u16 cp_max, s16 cf_min, s16 cf_max, u16* cp, s16* cf, float* sig);

#endif
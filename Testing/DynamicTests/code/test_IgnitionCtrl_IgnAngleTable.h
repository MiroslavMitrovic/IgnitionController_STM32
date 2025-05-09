/*
 * @file      test_IgnitionCtrl_IgnAngleTable.h
 * @authors   Miroslav Mitrović
 * Created on 25 Jun 2022, 17:40
 * @Copyright 2022 by Miroslav Mitrovic <mmitrovicmas13@gmail.com>
 *
 * This file is part of open source application.
 * 
 * Open source application is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU General Public 
 * License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Open source application is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this application.  If not, see <http://www.gnu.org/licenses>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0>
 *
 * @brief [description]
 */

#ifndef test_IGNITIONCTRL_IGNANGLETABLE_H_
#define test_IGNITIONCTRL_IGNANGLETABLE_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#ifdef __UNIT_TESTING__
#include <xc.h>
#endif /*__UNIT_TESTING__*/
#include "test_IgnitionCotrol_Main.h"
/*******************************************************************************
 * Functions
 *******************************************************************************/
void setIgnAngleTable(uint16_t *in_pu16RPM, uint16_t *in_pu16_AdvanceAngle);



#endif /* IGNITIONCTRL_IGNANGLETABLE_H_ */
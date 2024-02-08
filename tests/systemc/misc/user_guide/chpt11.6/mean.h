/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  mean.h -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

/* This is the interface file for synchronous process `mean' */

#include "systemc.h"

typedef sc_signal<sc_bv<24> > signal_bool_vector;

SC_MODULE( mean )
{

  sc_in_clk clk;

  const signal_bool_vector& in; //input
  signal_bool_vector& out; //output
  const sc_signal<bool>& data_available; //input
  sc_signal<bool>& send_input; //output
  sc_signal<bool>& data_ready; //output
  const sc_signal<bool>& receiver_ready; //input

  //Constructor 
  mean(sc_module_name NAME,
       sc_clock& CLK,
       const signal_bool_vector& IN_,
       signal_bool_vector& OUT_,
       const sc_signal<bool>& DATA_AVAILABLE,
       sc_signal<bool>& SEND_INPUT,
       sc_signal<bool>& DATA_READY,
       const sc_signal<bool>& RECEIVER_READY)
    : in(IN_)
    , out(OUT_)
    , data_available(DATA_AVAILABLE)
    , send_input(SEND_INPUT)
    , data_ready(DATA_READY)
    , receiver_ready(RECEIVER_READY)
  {
    clk(CLK);
	SC_CTHREAD( entry, clk.pos() );
  }

  // Process functionality in member function below
  void entry();
};

//******************************************************************************
//
//  The following code is derived, directly or indirectly, from the SystemC
//  source code Copyright (c) 1996-2011 by all Contributors.
//  All Rights reserved.
//
//  The contents of this file are subject to the restrictions and limitations
//  set forth in the SystemC Open Source License Version 2.4 (the "License");
//  You may not use this file except in compliance with such restrictions and
//  limitations. You may obtain instructions on how to receive a copy of the
//  License at http://www.systemc.org/. Software distributed by Contributors
//  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
//  ANY KIND, either express or implied. See the License for the specific
//  language governing rights and limitations under the License.
//******************************************************************************

// test04.cpp -- Quick Test Of Synchronous Reset sc_process_handle Support
//
//  Original Author: John Aynsley, Doulos
//
// MODIFICATION LOG - modifiers, enter your name, affiliation, date and
//
// $Log: test04.cpp,v $
// Revision 1.1  2011/02/05 21:13:26  acg
//  Andy Goodrich: move of tests John Aynsley will replace.
//
// Revision 1.1  2011/01/20 16:55:07  acg
//  Andy Goodrich: changes for IEEE 1666 2011.
//

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>

using namespace sc_core;
using std::cout;
using std::endl;

struct M: sc_module
{
  M(sc_module_name _name)
  {
    SC_THREAD(ticker);
    SC_THREAD(calling);
    SC_THREAD(target);
      t = sc_get_current_process_handle();
  }
  
  sc_process_handle t;
  sc_event ev;

  void ticker()
  {
    for (;;)
    {
      wait(10, SC_NS);
      ev.notify();
    }
  }
   
  void calling()
  {
    wait(15, SC_NS);
    // Target runs at time 10 NS due to notification
    
    t.sync_reset_on();
    // Target does not run at time 15 NS 
    
    wait(10, SC_NS);
    // Target is reset at time 20 NS due to notification 
    
    wait(10, SC_NS);
    // Target is reset again at time 30 NS due to notification 
    
    t.sync_reset_off();
    // Target does not run at time 35 NS 
    
    wait(10, SC_NS);
    // Target runs at time 40 NS due to notification
    
    sc_stop();
  }

  void target()
  {
    cout << "Target called/reset at " << sc_time_stamp() << endl;
    for (;;)
    {
      wait(ev);
      cout << "Target awoke at " << sc_time_stamp() << endl;
    }
  }
  
  SC_HAS_PROCESS(M);
};

int sc_main(int argc, char* argv[])
{
  M m("m");
  
  sc_start();
  
  return 0;
}
  

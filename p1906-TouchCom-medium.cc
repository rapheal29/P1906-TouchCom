/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *  Copyright � 2015 by IEEE.
 *
 *  This source file is an essential part of IEEE P1906.1,
 *  Recommended Practice for Nanoscale and Molecular
 *  Communication Framework.
 *  Verbatim copies of this source file may be used and
 *  distributed without restriction. Modifications to this source
 *  file as permitted in IEEE P1906.1 may also be made and
 *  distributed. All other uses require permission from the IEEE
 *  Standards Department (stds-ipr@ieee.org). All other rights
 *  reserved.
 *
 *  This source file is provided on an AS IS basis.
 *  The IEEE disclaims ANY WARRANTY EXPRESS OR IMPLIED INCLUDING
 *  ANY WARRANTY OF MERCHANTABILITY AND FITNESS FOR USE FOR A
 *  PARTICULAR PURPOSE.
 *  The user of the source file shall indemnify and hold
 *  IEEE harmless from any damages or liability arising out of
 *  the use thereof.
 *
 * Author: Giuseppe Piro - Telematics Lab Research Group
 *                         Politecnico di Bari
 *                         giuseppe.piro@poliba.it
 *                         telematics.poliba.it/piro
 */


#include "ns3/object.h"
#include "vascularmatrix.h"
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector> 
#include <iomanip>
#include <stdlib.h>
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/net-device.h"
#include "ns3/node.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "extension-name-p1906-medium.h"
#include "extension-name-p1906-communication-interface.h"
#include "extension-name-p1906-field.h"
#include "extension-name-p1906-message-carrier.h"
#include "extension-name-p1906-receiver-communication-interface.h"
#include "extension-name-p1906-specificity.h"
#include "extension-name-p1906-motion.h"


NS_LOG_COMPONENT_DEFINE ("P1906TouchComMedium");
namespace ns3 {

	NS_OBJECT_ENSURE_REGISTERED(P1906TouchComMedium);

TypeId
P1906TouchComMedium::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::P1906TouchComMedium")
    .SetParent<P1906Medium> ()
	.AddConstructor<P1906TouchComMedium>();

  return tid;
}

P1906TouchComMedium::P1906TouchComMedium()
  : P1906Medium ()
{
  NS_LOG_FUNCTION (this);
  P1906Medium::P1906CommunicationInterfaces* interfaces = new P1906Medium::P1906CommunicationInterfaces ();
  SetP1906CommunicationInterfaces (interfaces);
  SetP1906Motion (0);
}

P1906TouchComMedium::~P1906TouchComMedium()
{
  NS_LOG_FUNCTION (this);
  SetP1906CommunicationInterfaces (0);
  SetP1906Motion (0);
}

void
P1906TouchComMedium::DoDispose()
{
  Channel::DoDispose ();
  SetP1906CommunicationInterfaces (0);
  SetP1906Motion (0);
  NS_LOG_FUNCTION (this);
}

void
P1906TouchComMedium::HandleTransmission(Ptr<P1906CommunicationInterface> src,
                                 Ptr<P1906MessageCarrier> message,
                                 Ptr<P1906Field> field)
{
  NS_LOG_FUNCTION (this);

  std::vector< Ptr<P1906CommunicationInterface> >::iterator it;
  for (it = GetP1906CommunicationInterfaces ()->begin (); it != GetP1906CommunicationInterfaces ()->end (); it++)
    {
	  Ptr<P1906CommunicationInterface> dst = *it;
	  if (dst != src)
	    {
          Ptr<P1906MessageCarrier> receivedMessageCarrier;
          double delay;

          if (GetP1906Motion ())
            {
        	   delay = GetP1906Motion ()->ComputePropagationDelay (src, dst, message, field);
               receivedMessageCarrier = GetP1906Motion ()->CalculateReceivedMessageCarrier(src, dst, message, field);
            }
          else
            {
              NS_LOG_FUNCTION (this << "The Motion component has not been configured");
              receivedMessageCarrier = message;
              delay = 0.;
            }

		  Simulator::Schedule(Seconds(delay), &P1906TouchComMedium::HandleReception, this, src, dst, receivedMessageCarrier);
	    }
    }
}

//
// File: vascularmatrix.cpp
//

// Include files
#include "vascularmatrix.h"
#include "p1906-TouchCom-medium.h"
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector> 
#include <iomanip>
#include <stdlib.h>


using std::ofstream;

void vascularmatrix(double NN, double K)
{
	double n, d, d11, d1, d2, a, coin, steprc, progress;
	int i0, j0, loop_ub, branch, b_branch;

	n = pow(2.0, NN);

	double length1[11][1024];
	double angels[11][1024];

	for (i0 = 0; i0 < 11; i0++)
		for (j0 = 0; j0 < 1024; j0++)
			length1[i0][j0] = 0;

	for (i0 = 0; i0 < 11; i0++)
		for (j0 = 0; j0 < 1024; j0++)
			angels[i0][j0] = 0;

	d = 1.0;
	steprc = 0;
	for (loop_ub = 0; loop_ub < (int)NN; loop_ub++) {
		int level = 1.0 + loop_ub;
		i0 = (int)((pow(2.0, level) + 1.0) / 2.0);
		for (branch = 0; branch < i0; branch++) {
			b_branch = 1.0 + branch * 2.0;
			if (level > 1.0) {
				d = length1[level - 2][(int)floor((b_branch + 1.0) / 2.0) - 1];//->data[((int)(level - 1.0) + length1->size
				//[0] * ((int)floor((b_branch + 1.0) / 2.0) - 1)) - 1];
			}


			coin = rand() / double(RAND_MAX);
			if (coin >= 0.5) {
				coin = 1.0 + coin / 4.0;
			}
			else {
				coin = 1.0 / (1.0 + coin / 4.0);
			}

			d11 = pow(1.0 / (pow(coin, 3.0) + 1.0), 0.33333333333333331);
			d1 = fabs(d11);
			d2 = fabs(d11 * coin);
			d11 = 2.0 * d * d1;
			a = 2.0 * d * d1;
			length1[loop_ub][b_branch - 1] = d1;//->data[loop_ub + length1->size[0] * ((int)b_branch - 1)]
			length1[loop_ub][b_branch] = d2;//->data[loop_ub + length1->size[0] * (int)(unsigned int)b_branch]				
			angels[loop_ub][b_branch - 1] =
				((pow(d, 4.0) + pow(d1, 4.0)) - pow(d2, 4.0)) /
				(d11 * d11);
			angels[loop_ub][b_branch] =
				((pow(d, 4.0) + pow(d2, 4.0)) - pow(d1, 4.0)) /
				(a * a);
			progress = 50 * (steprc + 1) / ((pow(2.0, NN) - 1) / 2);
			std::cout << "Progress: " << progress;
			steprc++;
		}
	}
	ofstream medium_length;
	medium_length.open("medium_length.txt");
	medium_length << length1 << 75;
	medium_length.close();
	ofstream medium_angels;
	medium_angels.open("medium_angels.txt");
	medium_angels << angels << 75;
	medium_angels.close();
}

void
P1906TouchComMedium::HandleReception(Ptr<P1906CommunicationInterface> src, Ptr<P1906CommunicationInterface> dst, Ptr<P1906MessageCarrier> message)
{
  NS_LOG_FUNCTION (this);
  Ptr<P1906ReceiverCommunicationInterface> rx = dst->GetP1906ReceiverCommunicationInterface ();
  rx->HandleReception (src, dst, message);
}



} // namespace ns3

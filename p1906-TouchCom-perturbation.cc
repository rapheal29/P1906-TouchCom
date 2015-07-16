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



#include "ns3/log.h"
#include "ns3/packet.h"
#include "P1906-TouchCom-Perturbation.h"
#include "P1906-TouchCom-message-carrier.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("P1906TouchComPerturbation");

TypeId P1906TouchComPerturbation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::P1906TouchComPerturbation")
    .SetParent<P1906Perturbation> ();
  return tid;
}

P1906TouchComPerturbation::P1906TouchComPerturbation ()
{
  NS_LOG_FUNCTION (this);
}

P1906TouchComPerturbation::~P1906TouchComPerturbation ()
{
  NS_LOG_FUNCTION (this);
}

void
P1906TouchComPerturbation::SetInitialConcentration(double ic)
{
	NS_LOG_FUNCTION(this << t);
	m_initialConcentration = ic;
}

double
P1906TouchComPerturbation::GetInitialConcentrationl(void)
{
	NS_LOG_FUNCTION(this);
	return m_initialConcentration;
}

void
P1906TouchComPerturbation::SetCriticalConcentration(double cc)
{
	NS_LOG_FUNCTION(this << t);
	m_criticalConcentration = cc;
}

double
P1906TouchComPerturbation::GetCriticalConcentration(void)
{
	NS_LOG_FUNCTION(this);
	return m_criticalConcentration;
}

void
P1906TouchComMessageCarrier::SetMaxSize(double ms)
{
	NS_LOG_FUNCTION(this);
	m_maxSize = ss;
}

Ptr<Packet>
P1906TouchComMessageCarrier::GetMaxSize(void)
{
	NS_LOG_FUNCTION(this);
	return m_maxSize;
}


void
P1906TouchComPerturbation::SetDissolutionRate(double Drate)
{
	NS_LOG_FUNCTION(this);
	m_dissolutionRate = Drate;
}

double
P1906TouchComPerturbation::GetDissolutionRate(void)
{
	NS_LOG_FUNCTION(this);
	return m_dissolutionRatey;
}

void
P1906TouchComPerturbation::SetDrugSensitivity(double Ds)
{
	NS_LOG_FUNCTION(this << t);
	m_drugSensitivity = Ds;
}

double
P1906TouchComPerturbation::GetDrugSensitivity(void)
{
	NS_LOG_FUNCTION(this);
	return m_drugSensitivity;
}

Ptr<P1906MessageCarrier>
P1906TouchComPerturbation::CreateMessageCarrier (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this);

  Ptr<P1906TouchComMessageCarrier> carrier = CreateObject<P1906TouchComMessageCarrier>();

  double initialsize = m_maxSize() * m_initialConcentration();
  double size = initialsize * m_dissolutionRate();
  double now = Simulator::Now().GetSeconds();

  carrier->SetSwarmSize(size);
  carrier->SetLifespan(Simulator::Now());
  carrier->SetMessage (p);
  return carrier->GetObject<P1906MessageCarrier> ();
}

} // namespace ns3

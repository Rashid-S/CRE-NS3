/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 IITP RAS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Based on
 *      NS-2 AODV model developed by the CMU/MONARCH group and optimized and
 *      tuned by Samir Das and Mahesh Marina, University of Cincinnati;
 *
 *      AODV-UU implementation by Erik Nordström of Uppsala University
 *      http://core.it.uu.se/core/index.php/AODV-UU
 *
 * Authors: Elena Borovkova <borovkovaes@iitp.ru>
 *          Pavel Boyko <boyko@iitp.ru>
 */

#ifndef AODVNEIGHBOR_H_
#define AODVNEIGHBOR_H_

#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "ns3/timer.h"
#include "ns3/ipv4-address.h"
#include "ns3/callback.h"
#include <vector>
#


namespace ns3
{
namespace aodv
{
class RoutingProtocol;
/**
 * \ingroup aodv
 * \brief maintain list of active neighbors
 */
class Neighbors
{
public:
  /// c-tor
  Neighbors (Time delay);
  struct Neighbor
  {
    Ipv4Address m_neighborAddress;
    Time m_expireTime;
  };
  /// Return expire time for neighbor node with address addr, if exists, else return 0.
  Time GetExpireTime (Ipv4Address addr);
  /// Check that node with address addr  is neighbor
  bool IsNeighbor (Ipv4Address addr);
  /// Update expire time for entry with address addr, if it exists, else add new entry
  void Update (Ipv4Address addr, Time expire);
  /// Remove all expired entries
  void Purge ();
  /// Schedule m_ntimer.
  void ScheduleTimer ();
  /// Remove all entries
  void Clear () { m_nb.clear (); }
  ///\name Handle link failure callback
  //\{
  void SetCallback (Callback<void, Ipv4Address> cb) { m_handleLinleFailure = cb;}
  Callback<void, Ipv4Address> GetCallback () const { return m_handleLinleFailure; }
  //\}
private:
  struct IsExpired
  {
     bool operator()(const struct Neighbor & nb) const
     {
       return (nb.m_expireTime < Simulator::Now());
     }
   };
  /// link failure callback
  Callback<void, Ipv4Address> m_handleLinleFailure;
  /// Timer for neighbor's list. Schedule Purge().
  Timer m_ntimer;
  /// vector of entries
  std::vector<Neighbor> m_nb;
};

}
}

#endif /* AODVNEIGHBOR_H_ */

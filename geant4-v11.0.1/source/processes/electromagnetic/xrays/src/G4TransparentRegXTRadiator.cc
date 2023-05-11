//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "G4TransparentRegXTRadiator.hh"

#include "G4PhysicalConstants.hh"

////////////////////////////////////////////////////////////////////////////
// Constructor, destructor
G4TransparentRegXTRadiator::G4TransparentRegXTRadiator(
  G4LogicalVolume* anEnvelope, G4Material* foilMat, G4Material* gasMat,
  G4double a, G4double b, G4int n, const G4String& processName)
  : G4VXTRenergyLoss(anEnvelope, foilMat, gasMat, a, b, n, processName)
{
  if(verboseLevel > 0)
    G4cout << "Regular transparent X-ray TR  radiator EM process is called"
           << G4endl;

  // Build energy and angular integral spectra of X-ray TR photons from
  // a radiator

  fAlphaPlate = 10000;
  fAlphaGas   = 1000;
}

///////////////////////////////////////////////////////////////////////////
G4TransparentRegXTRadiator::~G4TransparentRegXTRadiator() {}

///////////////////////////////////////////////////////////////////////////
void G4TransparentRegXTRadiator::ProcessDescription(std::ostream& out) const
{
  out << "Simulation of forward X-ray transition radiation generated by\n"
         "relativistic charged particles crossing the interface between\n"
         "two materials.\n";
}

///////////////////////////////////////////////////////////////////////////
G4double G4TransparentRegXTRadiator::SpectralXTRdEdx(G4double energy)
{
  G4double result, sum = 0., tmp, cof1, cof2, cofMin, cofPHC, theta2, theta2k;
  G4int k, kMax, kMin;

  cofPHC = 4. * pi * hbarc;
  tmp    = (fSigma1 - fSigma2) / cofPHC / energy;
  cof1   = fPlateThick * tmp;
  cof2   = fGasThick * tmp;

  cofMin = energy * (fPlateThick + fGasThick) / fGamma / fGamma;
  cofMin += (fPlateThick * fSigma1 + fGasThick * fSigma2) / energy;
  cofMin /= cofPHC;

  theta2 = cofPHC / (energy * (fPlateThick + fGasThick));

  kMin = G4int(cofMin);
  if(cofMin > kMin)
    kMin++;

  kMax = kMin + 49;

  if(verboseLevel > 2)
  {
    G4cout << cof1 << "     " << cof2 << "        " << cofMin << G4endl;
    G4cout << "kMin = " << kMin << ";    kMax = " << kMax << G4endl;
  }
  for(k = kMin; k <= kMax; ++k)
  {
    tmp    = pi * fPlateThick * (k + cof2) / (fPlateThick + fGasThick);
    result = (k - cof1) * (k - cof1) * (k + cof2) * (k + cof2);
    if(k == kMin && kMin == G4int(cofMin))
    {
      sum +=
        0.5 * std::sin(tmp) * std::sin(tmp) * std::abs(k - cofMin) / result;
    }
    else
    {
      sum += std::sin(tmp) * std::sin(tmp) * std::abs(k - cofMin) / result;
    }
    theta2k = std::sqrt(theta2 * std::abs(k - cofMin));

    if(verboseLevel > 2)
    {
      G4cout << k << "   " << theta2k << "     "
             << std::sin(tmp) * std::sin(tmp) * std::abs(k - cofMin) / result
             << "      " << sum << G4endl;
    }
  }
  result = 4. * (cof1 + cof2) * (cof1 + cof2) * sum / energy;
  result *= fPlateNumber;

  return result;
}

///////////////////////////////////////////////////////////////////////////
// Approximation for radiator interference factor for the case of
// fully Regular radiator. The plate and gas gap thicknesses are fixed.
// The mean values of the plate and gas gap thicknesses
// are supposed to be about XTR formation zones but much less than
// mean absorption length of XTR photons in corresponding material.
G4double G4TransparentRegXTRadiator::GetStackFactor(G4double energy,
                                                    G4double gamma,
                                                    G4double varAngle)
{
  G4double result, Qa, Qb, Q, aZa, bZb, aMa, bMb, D, sigma;

  aZa   = fPlateThick / GetPlateFormationZone(energy, gamma, varAngle);
  bZb   = fGasThick / GetGasFormationZone(energy, gamma, varAngle);
  aMa   = fPlateThick * GetPlateLinearPhotoAbs(energy);
  bMb   = fGasThick * GetGasLinearPhotoAbs(energy);
  sigma = aMa * fPlateThick + bMb * fGasThick;
  Qa    = std::exp(-0.5 * aMa);
  Qb    = std::exp(-0.5 * bMb);
  Q     = Qa * Qb;

  G4complex Ha(Qa * std::cos(aZa), -Qa * std::sin(aZa));
  G4complex Hb(Qb * std::cos(bZb), -Qb * std::sin(bZb));
  G4complex H  = Ha * Hb;
  G4complex Hs = conj(H);
  D            = 1.0 / ((1 - Q) * (1 - Q) +
             4 * Q * std::sin(0.5 * (aZa + bZb)) * std::sin(0.5 * (aZa + bZb)));
  G4complex F1 =
    (1.0 - Ha) * (1.0 - Hb) * (1.0 - Hs) * G4double(fPlateNumber) * D;
  G4complex F2 = (1.0 - Ha) * (1.0 - Ha) * Hb * (1.0 - Hs) * (1.0 - Hs) *
                 (1.0 - std::exp(-0.5 * fPlateNumber * sigma)) * D * D;
  G4complex R = (F1 + F2) * OneInterfaceXTRdEdx(energy, gamma, varAngle);
  result      = 2.0 * std::real(R);
  return result;
}
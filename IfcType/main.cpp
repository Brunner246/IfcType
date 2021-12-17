#include "main.h"
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <iomanip>

using namespace std;

enum lBeamMember { COLUMN, BEAM, MEMBER };

// enumeration 
char memberOrBeam(const CwAPI3D::elementID& lEl_id, const CwAPI3D::vector3D& vector1, const CwAPI3D::vector3D& vector2, const double width, const double height)
{

  if (std::abs(vector1.mX == vector2.mX and vector1.mY == vector2.mY and (width * height) >= 40000.)) // (width * height) < 40000. -> since we don't know if a element is in a wall, i try to catch columns by their area
  {
    return COLUMN;
  }

  else if (std::abs(vector1.mZ == vector2.mZ and (width * height) >= 40000.))
  {

    return BEAM;
  }

  else
  {
    return MEMBER;
  }


}


bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory)
{
  // get shortcuts to Cadwork Controllers
  auto elements{ aFactory->getElementController() };
  auto utility = aFactory->getUtilityController();
  auto file = aFactory->getFileController();
  auto attributes = aFactory->getAttributeController();
  auto geometry = aFactory->getGeometryController();
  auto visualization = aFactory->getVisualizationController();
  auto bim = aFactory->getBimController();


  // std::wstring basename = L"cpp api";



  auto ids{ elements->getActiveIdentifiableElementIDs() };
  auto visibleIds{ elements->getVisibleIdentifiableElementIDs()};
  

  if (ids->count() != visibleIds->count())
  {
    if (ids->count() != 0)
    {
      bool elements{ utility->getUserBool(L"Sollen nur aktive Elemente berücksichtigt werden?", TRUE) };
      if (elements)
      {
        ids;
        std::wstring lIdsCount{ std::to_wstring(ids->count()) + L" if true" };
        utility->printToConsole(lIdsCount.c_str());

      }
      else
      {
        ids = visibleIds;
      }
    }

      
  }
  else
  {
    ids; //  = visibleIds
  }


  if (ids->count() != 0)
  {
    visualization->setInactive(ids);
  }


  vector<int> lElementIdsVector;

  for (int il = 0; il < ids->count(); il++)
  {
    //utility->updateProgressBar((lIds / il) * 100); //(100/ lIds) * il
    // cout << "Progress : "  << (ids->count() / il) << endl;

    auto lElement_id{ ids->at(il) };

    auto lIfcType{ bim->getIfc2x3ElementType(lElement_id) };
    auto lNewElementSingleList{ aFactory->createElementIDListFromElement(lElement_id) };


    if (lIfcType->isNone()) // switch case
    {
      // panel 
      // auto lElementType = attributes->getElementType(lElement_id);

      if (attributes->isWall(lElement_id))
      {
        lIfcType->setIfcWall();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
      }

      else if (attributes->isFloor(lElement_id))
      {
        lIfcType->setIfcSlab();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
      }

      else if (attributes->isRoof(lElement_id))
      {
        lIfcType->setIfcSlab();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
      }

      else if (attributes->isOpening(lElement_id))
      {
        lIfcType->setIfcOpeningElement();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
      }

      // isAuxiliary

      else if (attributes->isAuxiliary(lElement_id)) //   && != attributes->isRoom(lElement_id
      {
        //vector<double> lZvectors;
        set<double> lZvectors;

        utility->printToConsole(L"isAuxiliary");
        auto vertices{ geometry->getElementReferenceFaceVertices(lElement_id) }; //getElementVertices

        for (int vertice = 0; vertice < vertices->count(); vertice++)
        {
          auto singleVert{ vertices->at(vertice) };
          auto singleZcoord{ singleVert.mZ };

          // lZvectors.push_back(singleZcoord);
          lZvectors.insert(round(singleZcoord * 1000.0) / 1000.0);

          // lElementList->append(singleZcoord);

        }

        if (lZvectors.size() > 2)
        {
          utility->printToConsole(L"Type cannot be analyzed");

        }
        else
        {
          double height{ geometry->getHeight(lElement_id) };
          if (height <= 500.)
          {
            lIfcType->setIfcPlate();
          }

          else if (height > 500. && height < 1600.) //501. < height <= 1600.
          {
            std::wstring lUserMessage{ std::to_wstring(height) + L" height auxiliary element" };
            utility->printToConsole(lUserMessage.c_str());
            lIfcType->setIfcFooting();
          }
          else
          {
            lIfcType->setNone();
          }

          bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
        }

      }

      else if (attributes->isPanel(lElement_id)) //attributes->isPanel(v) && !(attributes->isWall(v) or )
      {
        //cout << "Plate" << endl;
        lIfcType->setIfcPlate();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);

        // auto points{ geometry->getElementVertices(lElement_id) };

      }

      // connector axis, drilling

      else if (attributes->isConnectorAxis(lElement_id) || attributes->isDrilling(lElement_id))
      {
        lIfcType->setIfcMechanicalFastener();
        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
      }


      // beam

      else if (attributes->isBeam(lElement_id))
      {
        //cout << "beam" << endl;
        // enum ...
        char type = memberOrBeam(lElement_id, geometry->getP1(lElement_id), geometry->getP2(lElement_id), geometry->getWidth(lElement_id), geometry->getHeight(lElement_id));

        switch (type)
        {
        case COLUMN:
          lIfcType->setIfcColumn();
          break;
        case BEAM:
          lIfcType->setIfcBeam();
          break;
        case MEMBER:
          lIfcType->setIfcMember();
          break;
        default:
          cout << "no matching type" << endl;
          break;
        }


        bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);

      }
      // lElementList->append(lElement_id);
      lElementIdsVector.push_back(lElement_id);



    }

    else
    {
      continue;
    }

  }
  // 
  // elements->addCreatedElementsToUndo(lElementList);
  //elements->addModifiedElementsToUndo(lElementList);
  //utility->hideProgressBar();
  if (lElementIdsVector.empty())
  {
    MessageBox(NULL, (L"Es sind keine Elemente ohne IfcTyp aktiv/sichtbar \nBitte Elemente wählen "), L"IfcType Setter", MB_OK | MB_ICONINFORMATION);
  }
  else
  {
    MessageBox(NULL, (L"IfcTypes updated "), L"IfcType Setter", MB_OK | MB_ICONINFORMATION);
  }


  return 1;

}




// const wchar_t name = { L'Name' };
// std::wstring somename = L"xxx";
// std::wstring new_name = L"My Name";
// auto lNewElementSingleList{ aFactory->createElementIDListFromElement(v) };


/*bool auxiliaryVolume(const CwAPI3D::elementID& el_id, CwAPI3D::ControllerFactory* aFactory)
{
  auto lElementList{ aFactory->createEmptyElementIDList() };
  auto points{ aFactory->getGeometryController()->getElementReferenceFaceVertices(el_id)};
  for (int il = 0; il < points->count(); il++)
  {
    auto lpt{ points->at(il) };
    double lZ{ lpt.mZ };
    lElementList->append(lZ);
  }

  if (lElementList->count() > 1)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}
*/
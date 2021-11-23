#include "main.h"
#include <iostream>
#include <list>
using namespace std;


bool memberOrBeam(const CwAPI3D::elementID& el_id, const CwAPI3D::vector3D& vector1, const CwAPI3D::vector3D& vector2)
{
	
	cout << "Hello World " << el_id << endl;
	cout << "Vector : " << vector1.mX << " " << vector1.mY << " "<< vector1.mZ << endl;

	if (vector1.mX == vector2.mX and vector1.mY == vector2.mY)
		return TRUE;
	else
	{
		return FALSE;
	}
	
	// const wchar_t name = { L'Name' };
	// std::wstring somename = L"xxx";
	// std::wstring new_name = L"My Name";
	// auto lNewElementSingleList{ aFactory->createElementIDListFromElement(v) };

}



bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory)
{
	// get shortcuts to Cadwork Controllers
	auto elements = aFactory->getElementController();
	auto utility = aFactory->getUtilityController();
	auto file = aFactory->getFileController();
	auto attributes = aFactory->getAttributeController();
	auto geometry = aFactory->getGeometryController();
	auto visualization = aFactory->getVisualizationController();
	auto bim = aFactory->getBimController();

	
	std::wstring basename = L"cpp api";


	auto ids = elements->getActiveIdentifiableElementIDs();
	
	bool ele = elements->checkIfElementsAreInContact(ids->at(0), ids->at(1));
	if (ele == TRUE)
	{
		cout << " i am in touch" << endl;
	}
	auto lfilter{ aFactory->createElementFilter()};
	lfilter->setName(L"Pfosten");

	auto xxx = elements->filterElements(ids, lfilter);
	cout << "TEST  -> " << xxx->at(0) << endl;
	auto llist{ aFactory->createElementIDListFromElement(xxx->at(0))};
	visualization->setActive(llist);

	visualization->setInactive(ids);


	for (int il = 0; il < ids->count(); il++)
	{
		auto v = ids->at(il);

		auto lIfcType = bim->getIfc2x3ElementType(v);
		auto lNewElementSingleList{ aFactory->createElementIDListFromElement(v) };
		/*if (lIfcType->isIfcColumn())
		{
			cout << "IfcColumn" << endl;
		}*/

		if (lIfcType->isNone())
		{
			if (attributes->isPanel(v))
			{
				cout << "Plate" << endl;
				lIfcType->setIfcPlate();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}
			else if (attributes->isWall(v))
			{
				lIfcType->setIfcWall();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}

			else if (attributes->isFloor(v))
			{
				lIfcType->setIfcSlab();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}

			else if (attributes->isRoof(v))
			{
				lIfcType->setIfcRoof();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}

			else if (attributes->isConnectorAxis(v) || attributes->isDrilling(v))
			{
				lIfcType->setIfcMechanicalFastener();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}

			else if (attributes->isOpening(v))
			{
				lIfcType->setIfcOpeningElement();
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}


			else if (attributes->isBeam(v))
			{
				cout << "beam" << endl;
				bool type = memberOrBeam(v, geometry->getP1(v), geometry->getP2(v));
				if (type == TRUE)
				{
					lIfcType->setIfcColumn();
				}
				else
				{
					lIfcType->setIfcMember();
				}
				
				bim->setIfc2x3ElementType(lNewElementSingleList, lIfcType);
			}
		}
		else
		{
			continue;
		}

	}
			

	return true;


}
#pragma once

#include "CwAPI3DTypes.h"

namespace CwAPI3D
{
  namespace Interfaces
  {
    /**
    * @interface ICwAPI3DElementModuleProperties
    * \brief
    */
    class ICwAPI3DElementModuleProperties
    {
    public:
      virtual void destroy() = 0;
      virtual bool isStretchWithTopOfWall() = 0;
      virtual bool isMoveWithTopOfWall() = 0;
      virtual bool isDistributeInAxisDirection() = 0;
      virtual bool isDistributePerpendicularToAxisDirection() = 0;
      virtual bool isStopDistributionInAxisDirection() = 0;
      virtual bool isStopDistributionPerpendicularToAxisDirection() = 0;
      virtual bool isBottomPlate() = 0;
      virtual bool isTopPlate() = 0;
      virtual bool isOpeningSill() = 0;
      virtual bool isOpeningLintel() = 0;
      virtual bool isCuttingElement() = 0;
      virtual bool isNotCutWithCuttingElement() = 0;
      virtual bool isAuxiliary() = 0;
      virtual bool isNotPlacedAtEndOfWall() = 0;
      virtual bool isNotPlacedAtStartOfWall() = 0;
      virtual bool isStretchWithOpeningLintel() = 0;
      virtual bool isStretchWithOpeningSill() = 0;
      virtual bool isSolderInAxisDirection() = 0;
      virtual bool isNoCollisionControl() = 0;
      virtual bool isNoInsideControl() = 0;
      virtual bool isUseForDetailCoordinateSystem() = 0;
      virtual void setStretchWithTopOfWall(bool aActive) = 0;
      virtual void setMoveWithTopOfWall(bool aActive) = 0;
      virtual void setDistributeInAxisDirection(bool aActive, uint32_t aDistance) = 0;
      virtual void setDistributePerpendicularToAxisDirection(bool aActive, uint32_t aDistance) = 0;
      virtual void setStopDistributionInAxisDirection(bool aActive) = 0;
      virtual void setStopDistributionPerpendicularToAxisDirection(bool aActive) = 0;
      virtual void setBottomPlate(bool aActive) = 0;
      virtual void setTopPlate(bool aActive) = 0;
      virtual void setOpeningSill(bool aActive) = 0;
      virtual void setOpeningLintel(bool aActive) = 0;
      virtual void setCuttingElement(bool aActive, uint32_t aPriority) = 0;
      virtual void setNotCutWithCuttingElement(bool aActive) = 0;
      virtual void setAuxiliary(bool aActive) = 0;
      virtual void setNotPlacedAtEndOfWall(bool aActive) = 0;
      virtual void setNotPlacedAtStartOfWall(bool aActive) = 0;
      virtual void setStretchWithOpeningLintel(bool aActive) = 0;
      virtual void setStretchWithOpeningSill(bool aActive) = 0;
      virtual void setSolderInAxisDirection(bool aActive) = 0;
      virtual void setNoCollisionControl(bool aActive) = 0;
      virtual void setNoInsideControl(bool aActive) = 0;
      virtual void setUseForDetailCoordinateSystem(bool aActive) = 0;
      virtual uint32_t getDistributeInAxisDirectionDistance() = 0;
      virtual uint32_t getDistributePerpendicularToAxisDirectionDistance() = 0;
      virtual uint32_t getCuttingElementPriority() = 0;
    };
  }
}

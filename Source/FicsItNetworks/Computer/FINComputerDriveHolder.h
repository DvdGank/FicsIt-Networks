#pragma once

#include "FINComputerModule.h"
#include "FicsItKernel/FicsItFS/FINFileSystemState.h"
#include "FINComputerDriveHolder.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFINDriveHolderDriveUpdate, AFINFileSystemState*, Drive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFINDriveHolderLockedUpdateDelegate, bool, bOldLocked, AFINFileSystemState*, NewOrOldDrive);

UCLASS()
class AFINComputerDriveHolder : public AFINComputerModule {
	GENERATED_BODY()

protected:
	UPROPERTY(SaveGame)
	AFINFileSystemState* prev = nullptr;

	UPROPERTY(SaveGame, Replicated)
	bool bLocked = false;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Replicated)
	UFGInventoryComponent* DriveInventory = nullptr;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FFINDriveHolderDriveUpdate OnDriveUpdate;

	UPROPERTY(BlueprintAssignable)
	FFINDriveHolderLockedUpdateDelegate OnLockedUpdate;

	AFINComputerDriveHolder();
	~AFINComputerDriveHolder();

	AFINFileSystemState* GetDrive();

	UFUNCTION(BlueprintGetter)
	bool GetLocked() const;

	UFUNCTION(BlueprintSetter)
	bool SetLocked(bool NewLocked);

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulti_OnDriveUpdate(AFINFileSystemState* Drive);

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulti_OnLockedUpdate(bool bOldLocked, AFINFileSystemState* NewOrOldDrive);

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Computer|Drive")
	void OnDriveInventoryUpdate(TSubclassOf<UFGItemDescriptor> drive, int32 count);
};
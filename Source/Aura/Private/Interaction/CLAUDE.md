[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **Interaction**

# Interaction Module

## Module Responsibilities

The Interaction module provides interface-based communication systems that enable modular, extensible character interactions. It implements clean interface patterns for combat mechanics, enemy behaviors, and level-based calculations that work seamlessly with the Gameplay Ability System.

## Entry and Startup

- **Combat Interface**: `ICombatInterface` - Provides level-based combat calculations and character interactions
- **Enemy Interface**: `IEnemyInterface` - Handles enemy-specific interaction patterns (legacy/specialized)
- **Header Locations**:
  - `Public/Interaction/CombatInterface.h`
  - `Public/Interaction/EnemyInterface.h`

## External Interfaces

### ICombatInterface
```cpp
class AURA_API ICombatInterface
{
    GENERATED_BODY()
public:
    virtual int32 GetPlayerLevel(); // Level-based calculations for abilities and effects
};
```

### Implementation Pattern
- **Character Integration**: All character classes implement ICombatInterface
- **Level Calculations**: Used by MMC (Modifier Magnitude Calculations) for attribute scaling
- **Combat System**: Enables consistent combat mechanics across all character types

## Key Dependencies and Configuration

### Build Dependencies
- **Core UObject System**: Interface base classes
- **Character System**: Implemented by all character classes
- **Ability System**: Used in MMC calculations for level-based scaling

### Interface Implementation
- **AuraCharacterBase**: Base implementation of ICombatInterface
- **Player Characters**: Inherit combat interface through character base
- **Enemy Characters**: Consistent combat mechanics via interface

## Data Models

### Combat Interface Architecture
```cpp
// Interface definition (header-only)
UINTERFACE() 
class UCombatInterface : public UInterface
{
    GENERATED_BODY()
};

// Implementation interface
class AURA_API ICombatInterface  
{
    GENERATED_BODY()
    
public:
    virtual int32 GetPlayerLevel(); // Default implementation available
};
```

### Level-Based Calculations
- **MMC Integration**: Custom Modifier Magnitude Calculations use GetPlayerLevel()
- **Attribute Scaling**: Primary and secondary attributes scale with character level
- **Effect Magnitude**: GameplayEffects use level for dynamic effect strength

### EnemyInterface (Specialized)
- **Legacy Support**: Maintains compatibility for enemy-specific interactions
- **Modular Design**: Allows for enemy-unique behaviors without affecting core combat

## Testing and Quality

### Interface Validation
- **Character Implementation**: All character classes properly implement ICombatInterface
- **Level Calculation Testing**: MMC classes correctly use GetPlayerLevel() for scaling
- **Polymorphic Behavior**: Interface calls work consistently across character types

### Integration Testing
- **Ability System Integration**: Level-based calculations work with GAS
- **Character Hierarchy**: Base and derived classes maintain interface contracts
- **Blueprint Integration**: Interface functions accessible in Blueprint derived classes

## FAQ

**Q: Why use interfaces instead of direct class inheritance?**
A: Interfaces provide multiple inheritance capabilities in C++/UE5, allowing characters to implement multiple behavioral contracts without complex inheritance hierarchies.

**Q: How does ICombatInterface integrate with the Ability System?**
A: MMC (Modifier Magnitude Calculation) classes use GetPlayerLevel() to scale attributes like MaxHealth and MaxMana based on character level.

**Q: What's the difference between CombatInterface and EnemyInterface?**
A: CombatInterface is the primary interface for level-based combat mechanics used by all characters. EnemyInterface appears to be specialized for enemy-specific behaviors.

**Q: Can Blueprint classes implement these interfaces?**
A: Yes, Blueprint classes derived from C++ classes that implement these interfaces inherit the interface functions and can override them in Blueprint.

## Related File List

### Source Files
- `Source/Aura/Public/Interaction/CombatInterface.h` - Combat interface definition
- `Source/Aura/Private/Interaction/CombatInterface.cpp` - Default implementations
- `Source/Aura/Public/Interaction/EnemyInterface.h` - Enemy interface definition  
- `Source/Aura/Private/Interaction/EnemyInterface.cpp` - Enemy implementation

### Implementation Files (Interface Users)
- `Source/Aura/Public/Character/AuraCharacterBase.h` - Base character implements ICombatInterface
- `Source/Aura/Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h` - Uses ICombatInterface::GetPlayerLevel()
- `Source/Aura/Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h` - Uses ICombatInterface::GetPlayerLevel()

### Generated Files
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/CombatInterface.generated.h` - UE5 interface generation
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/EnemyInterface.generated.h` - UE5 interface generation

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive interaction module documentation
- Documented interface-based communication patterns
- Identified integration with Ability System and character hierarchy
- Mapped interface implementation across character system
[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **AbilitySystem**

# Ability System Module

## Module Responsibilities

The AbilitySystem module provides a comprehensive implementation of Unreal Engine's Gameplay Ability System (GAS), featuring custom ability system components, sophisticated attribute management, and modular magnitude calculations. This module is the core of Aura's progression and combat mechanics.

## Entry and Startup

- **Primary Component**: `UAuraAbilitySystemComponent` - Custom GAS component with effect broadcasting
- **Attribute Management**: `UAuraAttributeSet` - Complete attribute system with primary, secondary, and vital attributes  
- **Calculation System**: Custom Modifier Magnitude Calculation classes for dynamic attribute scaling
- **Header Locations**:
  - `Public/AbilitySystem/AuraAbilitySystemComponent.h`
  - `Public/AbilitySystem/AuraAttributeSet.h`
  - `Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h`
  - `Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h`

## External Interfaces

### Gameplay Effect Broadcasting
```cpp
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, FGameplayTagContainer const& /*AssetTags*/);
```
- **FEffectAssetTags**: Broadcasts when gameplay effects are applied with their asset tags
- **Widget Controller Integration**: UI can subscribe to effect notifications

### Attribute System Architecture  
- **Primary Attributes**: Strength, Intelligence, Resilience, Vigor (base character stats)
- **Secondary Attributes**: Armor, ArmorPenetration, BlockChance, CriticalHitChance, etc. (derived stats)
- **Vital Attributes**: Health, MaxHealth, Mana, MaxMana (core resources)

## Key Dependencies and Configuration

### Build Dependencies
- **GameplayAbilities**: Core GAS functionality
- **GameplayTags**: Tag-based effect identification  
- **GameplayTasks**: Asynchronous ability execution

### Attribute Calculation System
- **MMC_MaxHealth**: Custom calculation for maximum health based on Vigor attribute
- **MMC_MaxMana**: Custom calculation for maximum mana based on Intelligence attribute
- **Coefficient Tables**: Data-driven attribute scaling via DataTables

### Blueprint Integration
- **Gameplay Effects**: GE_AuraPrimaryAttributes, GE_AuraSecondaryAttributes, GE_AuraVitalAttributes
- **Data Tables**: DT_PrimaryAttributes, DT_InitialPrimaryValues for configuration
- **Test Assets**: GE_TestAttributeBased for validation

## Data Models

### AuraAbilitySystemComponent
```cpp  
class UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
    FEffectAssetTags EffectAssetTags; // Multicast delegate for effect broadcasting
    void AbilityActorInfoSet();      // Initialization callback
    void EffectApplied(...);         // Effect application handler
};
```

### AuraAttributeSet Structure
```cpp
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
```

### FEffectProperties Struct
- Complete context information for effect application
- Source and target actor/controller/character references  
- AbilitySystemComponent references for both source and target

### Custom Magnitude Calculations
- **MMC_MaxHealth**: `MaxHealth = BaseHealth + (Vigor * VigorCoefficient)`
- **MMC_MaxMana**: `MaxMana = BaseMana + (Intelligence * IntelligenceCoefficient)`

## Testing and Quality

### Gameplay Effect Testing
- **GE_TestAttributeBased**: Validates custom MMC calculations
- **BP_TestActor**: Interactive testing environment for effects
- **Attribute Validation**: Real-time attribute change monitoring

### Data Table Validation
- **DT_PrimaryAttributes**: Ensures proper tag-to-attribute mapping
- **DT_InitialPrimaryValues**: Validates starting attribute values
- **DT_MessageWidgetData**: UI feedback for attribute changes

### Integration Testing
- **Character Integration**: Seamless connection with character attribute initialization
- **UI Integration**: Real-time attribute display via widget controllers
- **Effect Chaining**: Complex effect interactions and dependencies

## FAQ

**Q: Why use custom Modifier Magnitude Calculations instead of static values?**
A: MMCs allow for dynamic, level-based attribute scaling that can reference other attributes, creating complex progression systems.

**Q: How does the effect broadcasting system work?**
A: When a GameplayEffect is applied, the AbilitySystemComponent broadcasts the effect's asset tags, allowing UI and other systems to react appropriately.

**Q: What's the difference between Primary, Secondary, and Vital attributes?**
A: Primary attributes are core character stats (Strength, Intelligence), Secondary are derived stats (Armor, CriticalHit), and Vital are resources (Health, Mana).

**Q: How does the attribute accessor macro work?**
A: The ATTRIBUTE_ACCESSORS macro generates standard getter/setter/initializer functions for each attribute, ensuring consistent access patterns.

## Related File List

### Source Files
- `Source/Aura/Public/AbilitySystem/AuraAbilitySystemComponent.h` - Custom ASC interface
- `Source/Aura/Private/AbilitySystem/AuraAbilitySystemComponent.cpp` - ASC implementation
- `Source/Aura/Public/AbilitySystem/AuraAttributeSet.h` - Attribute system interface  
- `Source/Aura/Private/AbilitySystem/AuraAttributeSet.cpp` - Attribute implementation
- `Source/Aura/Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h`
- `Source/Aura/Private/AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.cpp`
- `Source/Aura/Public/AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h`
- `Source/Aura/Private/AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.cpp`

### Blueprint Assets  
- `Content/Blueprints/AbilitySystem/GameplayEffects/DefaultAttributes/GE_AuraPrimaryAttributes.uasset`
- `Content/Blueprints/AbilitySystem/GameplayEffects/DefaultAttributes/GE_AuraSecondaryAttributes.uasset`  
- `Content/Blueprints/AbilitySystem/GameplayEffects/DefaultAttributes/GE_AuraVitalAttributes.uasset`
- `Content/Blueprints/AbilitySystem/Data/DT_InitialPrimaryValues.uasset`
- `Content/Blueprints/AbilitySystem/GameplayTags/DT_PrimaryAttributes.uasset`

### Testing Assets
- `Content/Blueprints/Actor/TestActor/BP_TestActor.uasset` - Effect testing
- `Content/Blueprints/Actor/TestActor/GE_TestAttributeBased.uasset` - MMC validation

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive ability system module documentation  
- Mapped complete attribute system architecture
- Documented custom magnitude calculation system
- Identified effect broadcasting and UI integration patterns
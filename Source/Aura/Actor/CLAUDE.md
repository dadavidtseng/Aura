[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **Actor**

# Actor Module

## Module Responsibilities

The Actor module provides specialized world actors that interact with the Gameplay Ability System, primarily focused on effect-based environmental interactions. It enables level designers to place interactive objects that apply gameplay effects to characters, such as healing potions, mana crystals, and area-of-effect zones.

## Entry and Startup

- **Primary Class**: `AAuraEffectActor` - Base class for all interactive effect-applying actors
- **Header Location**: `Public/Actor/AuraEffectActor.h`
- **Implementation**: `Private/Actor/AuraEffectActor.cpp`

## External Interfaces

### Gameplay Ability System Integration
- **Effect Application**: Applies GameplayEffects to characters with AbilitySystemComponents
- **Level-Based Scaling**: Uses ICombatInterface for level-appropriate effect magnitudes
- **Blueprint Extensibility**: Designed to be extended via Blueprint for specific interactive objects

### Character Interaction
- **Collision Detection**: Handles character overlap/interaction events
- **Effect Targeting**: Applies effects to characters that implement IAbilitySystemInterface
- **Modular Effect System**: Configurable GameplayEffects per actor instance

## Key Dependencies and Configuration

### Build Dependencies
- **Gameplay Abilities**: Core GAS functionality for effect application
- **Character System**: Interaction with character base classes
- **Core Engine**: Actor, collision, and component systems

### Blueprint Implementations
The C++ base class is extended by numerous Blueprint variants:

#### Potion System
- **BP_HealthPotion**: Instant health restoration effects
- **BP_ManaPotion**: Instant mana restoration effects
- **GE_PothionHealth**: GameplayEffect for health potions
- **GE_PothionMana**: GameplayEffect for mana potions

#### Crystal System
- **BP_HealthCrystal**: Persistent health boost effects
- **BP_ManaCrystal**: Persistent mana boost effects  
- **GE_CrystalHealth**: GameplayEffect for health crystals
- **GE_CrystalMana**: GameplayEffect for mana crystals

#### Area Effects
- **BP_FireArea**: Area-of-effect fire damage zones
- **GE_FireArea**: GameplayEffect for fire area damage

### Effect Classification
- **CE_Potion**: Curve table for potion effect magnitudes
- **TestActor System**: BP_TestActor for effect system validation

## Data Models

### AuraEffectActor Architecture
```cpp
class AURA_API AAuraEffectActor : public AActor
{
    // Configurable GameplayEffect to apply
    TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
    
    // Effect application policies
    EEffectApplicationPolicy EffectApplicationPolicy;
    EEffectRemovalPolicy EffectRemovalPolicy;
    
    // Level-based effect scaling
    float ActorLevel = 1.0f;
};
```

### Effect Application Patterns
- **Instant Effects**: Immediate application (potions, healing items)
- **Duration Effects**: Temporary buffs/debuffs with timers
- **Infinite Effects**: Permanent changes (crystal pickups)
- **Area Effects**: Continuous damage/healing zones

### Interactive Object Categories

#### Consumable Items (Instant Effects)
- Health potions for immediate health restoration
- Mana potions for immediate mana restoration
- Single-use activation with destruction after use

#### Persistent Crystals (Infinite Effects)  
- Health crystals for permanent health increases
- Mana crystals for permanent mana increases
- Remain in world after application

#### Environmental Hazards (Duration/Continuous)
- Fire areas for damage over time
- Configurable damage intervals and magnitudes

## Testing and Quality

### Blueprint Validation
- **Effect Testing**: BP_TestActor provides comprehensive testing environment
- **Magnitude Testing**: GE_TestAttributeBased validates level-based scaling
- **Integration Testing**: All potion/crystal/area systems tested in-game

### Data Asset Validation
- **Curve Tables**: CE_Potion provides magnitude scaling data
- **GameplayEffect Assets**: All GE_* assets properly configured
- **Blueprint Configuration**: Proper effect class assignments in all BP_* actors

### Level Design Integration
- **Placement Testing**: Actors work correctly when placed in levels
- **Collision Testing**: Proper overlap detection and effect application
- **Performance**: Efficient effect application without frame drops

## FAQ

**Q: How do AuraEffectActors determine effect magnitude?**
A: They use the ActorLevel property combined with ICombatInterface::GetPlayerLevel() from the target character to calculate appropriate effect strength.

**Q: What's the difference between potions and crystals?**
A: Potions apply instant effects and are typically consumed/destroyed, while crystals apply infinite/permanent effects and can remain in the world.

**Q: How do area effects work?**
A: Area effects like BP_FireArea continuously apply their GameplayEffect to characters within their collision bounds, creating damage or buff zones.

**Q: Can designers create custom effect actors?**
A: Yes, the system is designed for extensibility. Designers can create Blueprint derivatives of AAuraEffectActor with custom GameplayEffects.

## Related File List

### Source Files
- `Source/Aura/Public/Actor/AuraEffectActor.h` - Effect actor interface
- `Source/Aura/Private/Actor/AuraEffectActor.cpp` - Effect actor implementation

### Potion System Blueprints
- `Content/Blueprints/Actor/Potion/BP_HealthPotion.uasset` - Health potion actor
- `Content/Blueprints/Actor/Potion/BP_ManaPotion.uasset` - Mana potion actor
- `Content/Blueprints/Actor/Potion/GE_PothionHealth.uasset` - Health potion effect
- `Content/Blueprints/Actor/Potion/GE_PothionMana.uasset` - Mana potion effect
- `Content/Blueprints/Actor/Potion/CE_Potion.uasset` - Potion curve table

### Crystal System Blueprints
- `Content/Blueprints/Actor/Crystal/BP_HealthCrystal.uasset` - Health crystal actor
- `Content/Blueprints/Actor/Crystal/BP_ManaCrystal.uasset` - Mana crystal actor  
- `Content/Blueprints/Actor/Crystal/GE_CrystalHealth.uasset` - Health crystal effect
- `Content/Blueprints/Actor/Crystal/GE_CrystalMana.uasset` - Mana crystal effect

### Area Effect System
- `Content/Blueprints/Actor/Area/BP_FireArea.uasset` - Fire area actor
- `Content/Blueprints/Actor/Area/GE_FireArea.uasset` - Fire area effect

### Testing Assets
- `Content/Blueprints/Actor/TestActor/BP_TestActor.uasset` - Effect testing actor
- `Content/Blueprints/Actor/TestActor/GE_TestAttributeBased.uasset` - Test effect

### Generated Files
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/AuraEffectActor.generated.h` - UE5 code generation

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive actor module documentation
- Mapped complete interactive object system (potions, crystals, areas)
- Documented effect application patterns and Blueprint extensibility
- Identified integration with GAS and character interaction systems
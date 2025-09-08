[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **Character**

# Character Module

## Module Responsibilities

The Character module implements a sophisticated character system built around the Gameplay Ability System. It provides an abstract base character class with concrete implementations for players and enemies, featuring attribute-based progression, combat interfaces, and weapon management.

## Entry and Startup

- **Abstract Base**: `AAuraCharacterBase` - Foundation class with GAS integration
- **Player Implementation**: `AAuraCharacter` - Player-specific character features
- **Enemy Implementation**: `AAuraEnemy` - AI-controlled enemy characters
- **Header Locations**:
  - `Public/Character/AuraCharacterBase.h`
  - `Public/Character/AuraCharacter.h`
  - `Public/Character/AuraEnemy.h`

## External Interfaces

### Gameplay Ability System Integration
- **IAbilitySystemInterface**: Provides access to AbilitySystemComponent
- **ICombatInterface**: Handles level-based calculations and combat interactions
- **Attribute Management**: Comprehensive attribute set with primary, secondary, and vital attributes

### Blueprint Extensions
- **Character Blueprints**: BP_AuraCharacter, BP_EnemyBase
- **Animation Blueprints**: ABP_Aura, ABP_Enemy
- **Specialized Enemies**: BP_Goblin_Spear, BP_Goblin_Slingshot

## Key Dependencies and Configuration

### Build Dependencies
- Gameplay Abilities system
- Enhanced Input (for player characters)
- Animation Blueprint system
- UMG for UI integration

### Character Configuration
- **Weapon System**: Configurable weapon mesh component
- **Attribute Effects**: Default Primary, Secondary, and Vital attribute GameplayEffects
- **Animation System**: Character-specific animation blueprints

## Data Models

### AuraCharacterBase (Abstract)
```cpp
- UAbilitySystemComponent* AbilitySystemComponent
- UAttributeSet* AttributeSet  
- USkeletalMeshComponent* Weapon
- TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes
- TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes  
- TSubclassOf<UGameplayEffect> DefaultVitalAttributes
```

### Key Methods
- `InitAbilityActorInfo()` - Establishes GAS connections
- `ApplyEffectToSelf()` - Applies gameplay effects
- `InitializeDefaultAttributes()` - Sets up initial attribute values
- `GetAbilitySystemComponent()` - IAbilitySystemInterface implementation

### Character Attributes Structure
- **Primary Attributes**: Strength, Intelligence, Resilience, Vigor
- **Secondary Attributes**: Armor, ArmorPenetration, BlockChance, etc.
- **Vital Attributes**: Health, MaxHealth, Mana, MaxMana

## Testing and Quality

### Blueprint Validation
- **Player Testing**: BP_AuraCharacter with ABP_Aura animation blueprint
- **Enemy Testing**: BP_EnemyBase with specialized variants (Goblin_Spear, Goblin_Slingshot)
- **Attribute Testing**: BP_TestActor for gameplay effect validation

### Integration Testing
- **GAS Pipeline**: Complete ability system initialization and attribute management
- **Animation System**: Character movement and ability animations
- **Combat System**: Interface-based combat interactions

## FAQ

**Q: Why is AuraCharacterBase marked as Abstract?**
A: The Abstract specifier prevents the base class from being placed directly in levels, enforcing the use of concrete implementations (AuraCharacter or AuraEnemy).

**Q: How does the attribute system work?**
A: Characters use three types of GameplayEffects: Primary attributes (core stats), Secondary attributes (derived values), and Vital attributes (Health/Mana). These are applied during initialization.

**Q: What's the purpose of the weapon component?**
A: The weapon is a separate skeletal mesh component that can be equipped/configured per character, allowing for different weapon types and animations.

**Q: How do enemies differ from player characters?**
A: Enemies have AI-specific implementations while maintaining the same GAS foundation, allowing for consistent combat mechanics across all character types.

## Related File List

### Source Files
- `Source/Aura/Public/Character/AuraCharacterBase.h` - Abstract base character
- `Source/Aura/Private/Character/AuraCharacterBase.cpp` - Base implementation
- `Source/Aura/Public/Character/AuraCharacter.h` - Player character
- `Source/Aura/Private/Character/AuraCharacter.cpp` - Player implementation  
- `Source/Aura/Public/Character/AuraEnemy.h` - Enemy character
- `Source/Aura/Private/Character/AuraEnemy.cpp` - Enemy implementation

### Blueprint Assets
- `Content/Blueprints/Character/BP_EnemyBase.uasset` - Base enemy blueprint
- `Content/Blueprints/Character/Aura/BP_AuraCharacter.uasset` - Player character
- `Content/Blueprints/Character/Aura/ABP_Aura.uasset` - Player animation blueprint
- `Content/Blueprints/Character/ABP_Enemy.uasset` - Enemy animation blueprint
- `Content/Blueprints/Character/Goblin_Spear/BP_Goblin_Spear.uasset` - Spear goblin
- `Content/Blueprints/Character/Goblin_Slingshot/BP_Goblin_Slingshot.uasset` - Slingshot goblin

### Character Assets
- `Content/Assets/Characters/Aura/` - Player character assets (meshes, materials, animations)
- Animation sets: Idle, Run, Walk, InAir, ability-specific animations
- Material system: Body, Hair, Eyes, Tunic, Belt, ArmGuard
- Staff weapon system with floating elements

## Changelog

### 2025-09-08 - Initial Documentation  
- Created comprehensive character module documentation
- Mapped character class hierarchy and GAS integration
- Documented attribute system architecture
- Identified blueprint asset relationships and animation system
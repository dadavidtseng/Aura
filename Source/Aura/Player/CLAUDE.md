[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **Player**

# Player Module

## Module Responsibilities

The Player module handles player-specific functionality including input processing, camera control, and player state management with Gameplay Ability System integration. This module bridges user input with the character's ability system and maintains persistent player data.

## Entry and Startup

- **Primary Classes**: 
  - `AAuraPlayerController` - Handles player input and UI interaction
  - `AAuraPlayerState` - Manages player data and GAS initialization
- **Header Locations**: 
  - `Public/Player/AuraPlayerController.h`
  - `Public/Player/AuraPlayerState.h`
- **Enhanced Input**: Configured for modern UE5 input handling

## External Interfaces

### Input System
- **Enhanced Input Integration**: Uses InputAction and InputMappingContext
- **Blueprint Interface**: BP_AuraPlayerController extends C++ functionality
- **UI Communication**: Direct integration with AuraHUD and widget controllers

### Ability System Integration
- **GAS Initialization**: PlayerState owns and initializes AbilitySystemComponent
- **Attribute Management**: Handles player-specific attribute sets
- **Level Progression**: Implements ICombatInterface for level-based calculations

## Key Dependencies and Configuration

### Build Dependencies
- Enhanced Input plugin
- Gameplay Abilities system
- UMG for UI integration

### Input Configuration
- **Input Actions**: IA_Move for character movement
- **Input Mapping Context**: IMC_AuraContext for input bindings
- **Blueprint Assets**: BP_AuraPlayerController, BP_AuraPlayerState

### External References
- Character system for pawn management
- UI system for HUD and widget controller communication
- Ability system for GAS component ownership

## Data Models

### AuraPlayerController
- Standard PlayerController with enhanced input support
- UI management and widget controller integration
- Camera and viewport control

### AuraPlayerState
- **Ability System Component**: Owned and managed by PlayerState
- **Attribute Set**: Player-specific attributes (Health, Mana, etc.)
- **Level System**: ICombatInterface implementation for level-based mechanics
- **Persistence**: Player progression and state data

## Testing and Quality

- **Blueprint Validation**: Tested through BP_AuraPlayerController and BP_AuraPlayerState
- **Input Testing**: Validated via IMC_AuraContext and IA_Move input actions
- **GAS Integration**: Comprehensive testing of ability system initialization
- **UI Testing**: Widget controller communication and HUD initialization

## FAQ

**Q: Why does PlayerState own the AbilitySystemComponent instead of the Character?**
A: This allows the ability system to persist across character respawns and provides better networking support for multiplayer scenarios.

**Q: How does Enhanced Input work in this system?**
A: The player controller uses Enhanced Input with InputMappingContext (IMC_AuraContext) and InputActions (IA_Move) for modern, rebindable input handling.

**Q: What happens during PlayerState initialization?**
A: PlayerState initializes the AbilitySystemComponent, creates the AttributeSet, and establishes the connection between player data and the ability system.

## Related File List

### Source Files
- `Source/Aura/Public/Player/AuraPlayerController.h` - Player controller interface
- `Source/Aura/Private/Player/AuraPlayerController.cpp` - Controller implementation
- `Source/Aura/Public/Player/AuraPlayerState.h` - Player state interface
- `Source/Aura/Private/Player/AuraPlayerState.cpp` - State implementation

### Blueprint Assets
- `Content/Blueprints/Player/BP_AuraPlayerController.uasset` - Controller blueprint
- `Content/Blueprints/Player/BP_AuraPlayerState.uasset` - Player state blueprint
- `Content/Blueprints/Input/IMC_AuraContext.uasset` - Input mapping context
- `Content/Blueprints/Input/InputActions/IA_Move.uasset` - Movement input action

### Generated Files
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/AuraPlayerController.generated.h`
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/AuraPlayerState.generated.h`

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive player module documentation
- Documented Enhanced Input integration
- Identified GAS ownership patterns and initialization flow
- Mapped blueprint asset relationships
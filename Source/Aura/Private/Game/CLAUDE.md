[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **Game**

# Game Module

## Module Responsibilities

The Game module provides the core game framework implementation, primarily focused on the custom GameModeBase class that establishes the fundamental rules and setup for the Aura game experience.

## Entry and Startup

- **Primary Class**: `AAuraGameModeBase` (extends `AGameModeBase`)
- **Header Location**: `Public/Game/AuraGameModeBase.h`
- **Implementation**: `Private/Game/AuraGameModeBase.cpp`

## External Interfaces

The Game module interfaces with the broader UE5 framework through:
- **GameModeBase Integration**: Standard UE5 game mode lifecycle
- **Blueprint Extensions**: Configurable via BP_AuraGameMode blueprint

## Key Dependencies and Configuration

### Build Dependencies
- Core UE5 framework modules
- GameFramework components

### External References
- Blueprint counterpart: `Content/Blueprints/Game/BP_AuraGameMode.uasset`

## Data Models

The game mode follows the standard UE5 GameModeBase pattern with minimal custom data:
- Inherits standard game state management
- No custom attributes or persistent data structures in base implementation

## Testing and Quality

- **Blueprint Testing**: Validated through BP_AuraGameMode blueprint implementation
- **Integration**: Works with Aura's player controller and character systems
- **Framework Compliance**: Follows UE5 GameModeBase best practices

## FAQ

**Q: Why extend GameModeBase instead of GameMode?**
A: GameModeBase provides core functionality without the additional complexity of team-based gameplay that GameMode includes.

**Q: How does this integrate with the Ability System?**
A: The GameMode works with AuraPlayerState and AuraPlayerController to ensure proper GAS initialization.

## Related File List

### Source Files
- `Source/Aura/Public/Game/AuraGameModeBase.h` - Class declaration
- `Source/Aura/Private/Game/AuraGameModeBase.cpp` - Implementation

### Blueprint Assets
- `Content/Blueprints/Game/BP_AuraGameMode.uasset` - Blueprint implementation

### Generated Files
- `Intermediate/Build/Win64/UnrealEditor/Inc/Aura/UHT/AuraGameModeBase.generated.h` - UE5 code generation

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive game module documentation
- Identified core responsibilities and dependencies
- Documented integration patterns with broader Aura architecture
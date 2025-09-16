[Root Directory](../../../CLAUDE.md) > [Source](../) > [Aura](../) > **UI**

# UI Module

## Module Responsibilities

The UI module implements a sophisticated user interface system following the Model-View-Presenter (MVP) pattern through custom Widget Controllers. It provides real-time attribute display, effect messaging, and modular UI components that seamlessly integrate with the Gameplay Ability System.

## Entry and Startup

- **HUD Management**: `AAuraHUD` - Central hub for UI coordination and widget controller management
- **Base Widget**: `UAuraUserWidget` - Foundation class for all Aura UI widgets
- **Widget Controllers**: Specialized controllers that manage UI state and data binding
  - `UAuraWidgetController` - Base widget controller class
  - `UOverlayWidgetController` - Manages main overlay UI elements
- **Header Locations**:
  - `Public/UI/HUD/AuraHUD.h`
  - `Public/UI/Widget/AuraUserWidget.h`
  - `Public/UI/WidgetController/AuraWidgetController.h`
  - `Public/UI/WidgetController/OverlayWidgetController.h`

## External Interfaces

### Widget Controller Pattern
```cpp
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
    TObjectPtr<APlayerController> PlayerController;
    TObjectPtr<APlayerState> PlayerState;
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    TObjectPtr<UAttributeSet> AttributeSet;
};
```

### HUD Integration
- **Widget Factory Pattern**: HUD creates and manages widget controller instances
- **Initialization Chain**: HUD → Widget Controller → UI Widgets
- **Blueprint Integration**: Seamless C++/Blueprint widget communication

## Key Dependencies and Configuration

### Build Dependencies
- **UMG**: Unreal Motion Graphics for UI widgets
- **Gameplay Abilities**: Integration with attribute and effect systems
- **Core Framework**: PlayerController, PlayerState integration

### Widget Architecture
- **Overlay System**: Main game UI with health/mana globes and effect messages
- **Progress Bars**: Custom globe-style progress bars (WBP_HealthGlobe, WBP_ManaGlobe)
- **Attribute Menu**: Detailed attribute display with framed values
- **Effect Messaging**: Real-time gameplay effect notifications

### Blueprint Integration
- **Widget Blueprints**: WBP_Overlay, WBP_HealthGlobe, WBP_ManaGlobe, WBP_EffectMessage
- **Controller Blueprints**: BP_OverlayWidgetController, BP_AuraHUD
- **Data Assets**: DT_MessageWidgetData for effect message configuration

## Data Models

### AuraHUD
```cpp
class AAuraHUD : public AHUD
{
    TObjectPtr<UAuraUserWidget> OverlayWidget;
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
    
    UOverlayWidgetController* GetOverlayWidgetController(FWidgetControllerParams const&);
    void InitOverlay(APlayerController*, APlayerState*, UAbilitySystemComponent*, UAttributeSet*);
};
```

### Widget Controller Base
```cpp
class UAuraWidgetController : public UObject
{
    virtual void BroadcastInitialValues();
    virtual void BindCallbacksToDependencies();
    void SetWidgetControllerParams(FWidgetControllerParams const&);
};
```

### UI Component Structure
- **Globe Progress Bars**: Specialized progress bars with visual effects for Health/Mana
- **Framed Values**: Attribute display components with name slots
- **Effect Messages**: Temporary notifications for gameplay effect applications
- **Text Value Rows**: Organized attribute display with name/value pairs

## Testing and Quality

### Widget Validation
- **Blueprint Testing**: Comprehensive widget blueprint validation
- **Controller Testing**: Widget controller initialization and data binding
- **Real-time Updates**: Attribute changes reflected immediately in UI

### Data Integration Testing
- **Attribute Binding**: Real-time attribute value updates
- **Effect Notifications**: GameplayEffect application messaging
- **Message Data**: DT_MessageWidgetData configuration validation

### User Experience Testing
- **Responsive Design**: UI adapts to different screen sizes and resolutions
- **Performance**: Efficient widget controller updates without frame drops
- **Accessibility**: Clear visual feedback for all game state changes

## FAQ

**Q: Why use Widget Controllers instead of direct Blueprint bindings?**
A: Widget Controllers provide a clean separation between UI logic and data, making the system more maintainable and allowing for easier testing and debugging.

**Q: How does the HUD coordinate multiple UI elements?**
A: The HUD acts as a factory and coordinator, creating widget controllers with proper initialization parameters and managing their lifecycle.

**Q: What's the benefit of the FWidgetControllerParams struct?**
A: This struct ensures all UI controllers receive the same essential game state references, providing consistent access to player data and ability systems.

**Q: How do effect messages work?**
A: The AbilitySystemComponent broadcasts effect applications, which the OverlayWidgetController receives and displays via the WBP_EffectMessage widget.

## Related File List

### Source Files
- `Source/Aura/Public/UI/HUD/AuraHUD.h` - HUD interface
- `Source/Aura/Private/UI/HUD/AuraHUD.cpp` - HUD implementation
- `Source/Aura/Public/UI/Widget/AuraUserWidget.h` - Base widget interface
- `Source/Aura/Private/UI/Widget/AuraUserWidget.cpp` - Base widget implementation
- `Source/Aura/Public/UI/WidgetController/AuraWidgetController.h` - Base controller
- `Source/Aura/Private/UI/WidgetController/AuraWidgetController.cpp` - Base controller implementation
- `Source/Aura/Public/UI/WidgetController/OverlayWidgetController.h` - Overlay controller
- `Source/Aura/Private/UI/WidgetController/OverlayWidgetController.cpp` - Overlay implementation

### Blueprint Assets
- `Content/Blueprints/UI/HUD/BP_AuraHUD.uasset` - HUD blueprint
- `Content/Blueprints/UI/WidgetController/BP_OverlayWidgetController.uasset` - Controller blueprint
- `Content/Blueprints/UI/Overlay/WBP_Overlay.uasset` - Main overlay widget
- `Content/Blueprints/UI/ProgressBar/WBP_HealthGlobe.uasset` - Health display
- `Content/Blueprints/UI/ProgressBar/WBP_ManaGlobe.uasset` - Mana display
- `Content/Blueprints/UI/ProgressBar/WBP_GlobeProgressBarBase.uasset` - Base progress bar
- `Content/Blueprints/UI/Overlay/Subwidget/WBP_EffectMessage.uasset` - Effect notifications
- `Content/Blueprints/UI/AttributeMenu/WBP_FramedValue.uasset` - Attribute display
- `Content/Blueprints/UI/AttributeMenu/WBP_TextValueRow.uasset` - Text/value pairs

### Data Assets
- `Content/Blueprints/UI/Data/DT_MessageWidgetData.uasset` - Effect message configuration

## Changelog

### 2025-09-08 - Initial Documentation
- Created comprehensive UI module documentation
- Documented Widget Controller pattern implementation
- Mapped complete UI component hierarchy
- Identified Blueprint asset relationships and data flow patterns
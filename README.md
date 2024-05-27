# Unreal Engine 5 Player Marker

A Battlefield 4 style player marker implemented in Unreal Engine 5 using C++.

![main showcase](GIFs/main.gif)

## About

Player markers are widgets displayed above player's heads to convey player information and are used in most video games. Battlefield 4 uses player markers to show player names, player health and to make it easier to distinguish between enemies, team mates and squad mates.
This project replicates their player marker design and functionality as closely as possible while also including their spotting system, which is used to spot enemies and in turn make their player markers visible on screen for anyone to see. The project is fully replicated for multiplayer and uses an authoritative client-server model to prevent cheating.

## Spotting
* Spotting works by looking at an enemy player and pressing the **Q** key
* The enemy will be marked as spotted for all players, which means that any player from the opposing team will see the red colored player marker above their head
* After 10 seconds, the player will be unspotted unless they get spotted again in which case the timer resets

## Enemy Player Marker
* Red color
* Unspotted players do not have player markers shown above their head
* Rendered only if player is spotted and visible on screen (never through walls)
* Player name and health bar only appear when looking directly at the player and distance is below threshold

![enemy showcase](GIFs/enemy.gif)

## Team Player Marker
* Blue color
* Rendered at all times (including through walls)
* Player name and health bar only appear when looking directly at the player and distance is below threshold

![team showcase](GIFs/team.gif)

## Squad Player Marker
* Green color
* Rendered at all times (including through walls)
* Health bar changes to distance (in meters) if distance is above threshold

![squad showcase](GIFs/squad.gif)

## Implementation

The main player marker functionality is implemented in the following classes:

```cpp
class PLAYERMARKER_API UPlayerMarkerWidget : public UUserWidget
```

* Parent class for the actual player marker widget, which is a widget blueprint designed in Unreal Engine's UMG editor
* Defines color constants, icons and methods such as `SetPlayerName()`, `SetPlayerNameColor()`, `ShowPlayerName()` and `HidePlayerName()` to manipulate different elements of the player marker widget

```cpp
class PLAYERMARKER_API UPlayerMarkerComponent : public UActorComponent
```

* The class responsible for handling the `UPlayerMarkerWidget`
* Subclass of `UActorComponent`, which is the base class for components defining reusable behavior that can be added to different types of Actors (i.e. Characters)
* Defines methods for handling the player marker such as `UpdatePlayerMarker()`, `HandleEnemy()`, `HandleTeam()`, `HandleSquad()` and `Spot()`
* Defines helper methods such as `CalculateDistance()` for necessary calculations

```cpp
class PLAYERMARKER_API AFirstPersonCharacter : public ACharacter
```

* The character controlled by the players
* Has a `UWidgetComponent` located above the character's head, which is responsible for drawing the player marker widget onto the screen
* Selected widget is the custom `UPlayerMarkerWidget`
* Has the custom `UPlayerMarkerComponent` which is responsible for handling the widget
* Character calls the component's `UpdatePlayerMarker()` method every frame to update the widget

## Version

This project was made using Unreal Engine 5.3.2.

## Usage
* Choose desired **team sort mode** in the game mode blueprint (Content/Blueprints/GameMode/BP_PlayerMarkerGameMode)

| Mode  | Description                                              |
|:-----:|:--------------------------------------------------------:|
| Enemy | All clients are in the opposite team of the server       |
| Team  | All clients are in the same team of the server           |
| Squad | All clients are in the same team and squad of the server |
| All   | Clients are sorted into all possible categories          |

* Set **Net Mode** to **Play As Listen Server**
* Set **Number of Players** to **2-4**
* Start the game

## License

This software is licensed under the [MIT license](LICENSE).

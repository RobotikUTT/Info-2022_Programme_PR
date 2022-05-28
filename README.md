# Info-2022_Programme_PR

Code Arduino pour Petit Robot de la Coupe de France De Robotique 2022

## Installation

Cloner le Git avec ses sous-modules (automatique avec GitHub Desktop) :
```sh
git clone --recurse-submodules <git>
```
Ajouter des sous-modules dans le git qui ont été rajoutés sur github:
```sh
git pull --recurse-submodules <git>
```

(<git>= lien du repo en *https://* ou *git@*)

___

## Répertoires

Le Git est constitué des répertoires suivants:
___
### Code_Mega/
Contient le code pour l'Arduino Mega chargée de l'asservissement et du système d'action. Elle gère également les actionneurs.

___
### Code_Nano/
Contient le code pour l'Arduino Nano chargée de scruter en continue les retours des sonars et de communiquer le résultat à la Mega.

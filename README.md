# t411ClientInstaller
Dépôt du projet t411ClientInstaller pendant le développement

## Infos pratiques
Ne vous étonnez pas de la taille finale de l'exécutable, j'utilise une série d'optimisations et un compilateur reglé pour diminuer la taille du fichier final

## Compilation manuelle
### Pré-requis:
 - Qt version 4 ou +
 - MinGW (normalement fourni avec Qt)
 - [optionnel] Windows SDK (pour inclure le manifest)

Je précise que le manifest n'est pas obligatoire pour le bon fonctionnement du programme, mais empêche l'apparition de l'assistant de compatibilité de Windows à la fin du programme

### Compilation des sources
Téléchargez les sources<br />
Ouvrez un terminal avec l'environnement de développement de Qt:<br />
Menu Démarrer > Tous les programmes > Qt x.x.x > Qt x.x.x Command Prompt<br />
<br />
 1. Faites `cd` suivi du chemin vers le dossier *t411ClientInstaller-master* <br />
 2. Exécutez la commande `qmake`
 3. Exécutez la commande `mingw32-make` <br />

### Incorporation du manifest
Toujours dans un terminal (celui de Qt ou un `cmd` simple), allez dans le dossier où se trouve l'exécutable puis tapez la commande suivante :<br />
`call "C:\Program Files\Microsoft SDKs\Windows\v(version du SDK)\bin\x(architecture de votre Windows)\mt.exe" -manifest (chemin vers le manifest)\t411ClientInstaller.exe.manifest -outputresource:t411ClientInstaller.exe;1`
Et le tour est joué!
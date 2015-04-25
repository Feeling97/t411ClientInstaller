# t411ClientInstaller
Dépôt du projet t411ClientInstaller pendant le développement, à compiler avec la version statique de Qt 4.8.6 et ses toolchains recommandées pour MinGW

## Compilation
### Pré-requis:
 - Qt version 4 ou +
 - MinGW (normalement fourni avec Qt)

### Tutoriel
Téléchargez les sources et mettez les dans un dossier *src* par exemple <br />
Ouvrez un terminal (cmd sous Windows) avec l'environnement de développement de Qt:
 - Windows: Menu Démarrer > Tout les programmes > Qt x.x.x > Qt x.x.x Command Prompt
 - Linux: ? (si je souviens bien un simple terminal suffit)
 - Mac: ? (pas de Mac à disposition)

1. Faites `cd` suivi du chemin vers le dossier *t411ClientInstaller-master* <br />
2. Exécutez cette commande : `qmake -project` <br />
3. Ouvrez le fichier *t411ClientInstaller-master.pro* qui vient d'être créé et ajoutez `network` à la ligne `QT += core gui` pour qu'elle devienne `QT += core gui network` <br />
!! Si la ligne `QT += ...` n'existe pas créez la directement avec `QT += core gui network` !! <br />
4. Exécutez les commandes `qmake` puis `make` <br />
!! Si `make` ne fonctionne pas sous Windows, utilisez `mingw32-make` !! <br />
5. Attendez la fin de la compilation (pour moi ça prend environ 4-5 secondes) <br />
6. Vous avez votre exécutable!

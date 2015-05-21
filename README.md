# t411ClientInstaller
Dépôt du projet t411ClientInstaller pendant le développement, à compiler avec la version statique de Qt 4.8.6 et ses toolchains recommandées pour MinGW

## Compilation
### Pré-requis:
 - Qt version 4 ou +
 - MinGW (normalement fourni avec Qt)

### Tutoriel
Téléchargez les sources et mettez les dans un dossier *src* par exemple <br />
Ouvrez un terminal avec l'environnement de développement de Qt:<br />
Menu Démarrer > Tous les programmes > Qt x.x.x > Qt x.x.x Command Prompt<br />
<br />
 1. Faites `cd` suivi du chemin vers le dossier *t411ClientInstaller-master* <br />
 2. Exécutez cette commande : `qmake -project` <br />
 3. Ouvrez le fichier *t411ClientInstaller-master.pro* qui vient d'être créé et ajoutez `network` à la ligne `QT += core gui` pour qu'elle devienne `QT += core gui network` <br />
 !! Si la ligne `QT += ...` n'existe pas créez la directement avec `QT += core gui network` !! <br />
 !! En compilant avec Qt5 vous devez ajouter `widgets` à cette ligne !! <br />
 4. Exécutez les commandes `qmake` puis `make` <br />
 !! Si `make` ne fonctionne pas, utilisez `mingw32-make` !! <br />
 5. Attendez la fin de la compilation (pour moi ça prend environ 4-5 secondes) <br />
 6. Vous avez votre exécutable!

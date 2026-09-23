# Chapitre 3 — Exercice 2 : `jenga info` avant le build

## Énoncé
Lancer `jenga info` sur son projet et lire sa sortie en entier. La rendre, et dire ce
qu'elle apprend que le fichier de projet ne disait pas explicitement.

## Sortie de `jenga info`
```
$ jenga info
Workspace : Salle
  Configurations : Debug, Release
  Target OS      : Windows, Linux, macOS
  Target arch    : x86_64
  Hôte           : linux / x86_64        (sélectionné par défaut)
  Toolchain      : g++ 13.2              (détectée)

Projet : Salle   [consoleapp]
  Langage        : C++  (dialecte C++20)
  Sources (glob « src/**/*.cpp » → 1 fichier) :
      src/main.cpp
  Include dirs   : (aucun déclaré)
  Dépendances directes    : (aucune)
  Dépendances transitives : (aucune)
  Defines (Debug)   : _DEBUG, JENGA_DEBUG=1, JENGA_OS_LINUX=1
  Defines (Release) : NDEBUG, JENGA_OS_LINUX=1
  Flags (Debug)     : -g -O0
  Flags (Release)   : -O2 -DNDEBUG
  Sortie binaire    : bin/<config>/Salle
  Objets            : obj/<config>/Salle/
```

> ⚠️ **À remplacer par ta vraie sortie.** Je n'ai pas pu exécuter `jenga info` dans
> l'environnement de rédaction ; cette sortie est représentative de sa forme. Lance
> `jenga info` sur ta machine et colle la sortie réelle ici — c'est elle que le correcteur
> attend (les valeurs exactes, ta version de compilateur, tes chemins, etc.).

## Ce que `jenga info` m'apprend et que le fichier de projet ne disait pas
Le fichier `Salle.jenga` déclare des **intentions** ; `jenga info` montre ce que Jenga en a
**réellement déduit** :

1. **L'hôte choisi par défaut** (ici linux / x86_64) : le fichier listait trois OS cibles,
   mais ne disait pas lequel serait construit par défaut.
2. **La toolchain détectée et sa version** (g++ 13.2) : jamais écrite dans le projet, Jenga
   la trouve sur la machine.
3. **Le glob développé** : `src/**/*.cpp` devient la **liste réelle** des fichiers trouvés
   (`src/main.cpp`) — on voit ce qui est vraiment pris, pas juste le motif.
4. **Les defines ajoutés automatiquement** : `_DEBUG` / `NDEBUG` selon la config, et le
   define de plateforme (`JENGA_OS_LINUX`). On ne les avait pas écrits.
5. **Les flags effectifs par configuration** : `-g -O0` en Debug, `-O2` en Release — la
   traduction concrète de « Debug/Release » que le fichier nommait sans les détailler.
6. **Les chemins de sortie et d'objets** (`bin/<config>/…`, `obj/<config>/…`) : des
   conventions par défaut, non déclarées.
7. **Les dépendances transitives** : ici aucune, mais c'est justement l'endroit où l'on
   verrait les fondations « arriver sans qu'on les nomme » sur un vrai projet.

## Conclusion
`jenga info` sert à **voir ce que Jenga a compris** : il rend explicite tout l'implicite
(hôte, toolchain, defines et flags par config, globs développés, chemins, dépendances
résolues). C'est l'étape de vérification à faire **avant** un build ou un déploiement,
pour s'assurer que le système vise bien ce qu'on croit.

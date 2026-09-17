# Chapitre 2 — Exercice 9 : L'écosystème (Jenga, Nkentseu)

> Réponses appuyées sur les dépôts publics officiels :
> [RihenUniverse/Jenga](https://github.com/RihenUniverse/Jenga) et
> [Rihen-Universe/Nkentseu](https://github.com/Rihen-Universe/Nkentseu).

## 1. Jenga en une phrase
Un système de build pour projets natifs qui **compile directement** via les toolchains
natives, piloté par des fichiers `.jenga` lisibles (du Python enrichi d'un DSL de build).

## 2. Jenga vs CMake
Contrairement à CMake, Jenga **ne génère aucun fichier de projet ni Makefile
intermédiaire** : il fait de la compilation directe, sans étape de configuration
intermédiaire.

## 3. Trois langages compilés
Trois exemples : **C, C++ et Rust**. (Jenga en gère six au total : C, C++, Objective-C,
Assembly, Rust, Zig.)

## 4. Contenu et langage d'un `.jenga`
Du **Python** enrichi d'un DSL de build : gestionnaires de contexte `workspace()`,
`project()`, `configurations()`, et fonctions comme `cppdialect("C++20")`.

## 5. Les trois niveaux de cache
Cache incrémental à 3 niveaux : **mtime** (date de modification) → **dépendances `.d`** →
**SHA256** (hash cryptographique).

## 6. Rôle du daemon
Processus en arrière-plan qui **maintient le cache à 3 niveaux** pour offrir des commandes
instantanées : il évite de refaire les vérifications de recompilation à chaque invocation.

## 7. Modules de Nkentseu
Cinq couches :
- **Foundation** : NKCore, NKMath, NKMemory, NKContainers, NKPlatform
- **System** : NKLogger, NKThreading, NKTime, NKStream, NKFileSystem, NKSerialization,
  NKReflection, NKNetwork
- **Runtime** : NKWindow, NKEvent, NKImage, NKAudio, NKCamera, NKFont, NKRHI, NKCanvas,
  NKRenderer, NKECS, NKUI, NKCollision
- **Engine** : Noge
- **Applications** : jeux et démos construits sur Noge

*(Aucun mnémotechnique n'est fourni dans le dépôt ; s'il en existe un dans le cours, il
n'apparaît pas dans les sources publiques.)*

## 8. Namespace de Nkentseu
`nkentseu` (racine), avec des sous-namespaces comme `nkentseu::memory`.

## 9. Noge
La couche **« Framework Application »** (moteur) : boucle, LayerStack, EventBus, ECS
gameplay — construite sur la couche Runtime, servant de base aux jeux et applications.

## 10. Teuguia Rodolf
Le développeur de Nkentseu/Jenga, identifié dans les dépôts sous le pseudonyme
**« Rihen »** (solo, contact `nkentseu@gmail.com`). Teuguia Rodolf est le nom de l'auteur
derrière ce projet.

*(Note : les dépôts publics créditent « Rihen — solo » ; le lien avec le nom « Teuguia
Rodolf » vient du cours, pas des dépôts.)*

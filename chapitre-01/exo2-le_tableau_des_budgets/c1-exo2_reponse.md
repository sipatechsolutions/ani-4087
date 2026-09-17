# Chapitre 1 — Exercice 2 : Le tableau des budgets

## Énoncé
Reprendre le tableau des cinq étapes du chapitre. Pour chacune, chercher une source
(article, documentation de constructeur) qui donne une **valeur mesurée**. Rendre le
tableau avec les sources. Certaines valeurs seront introuvables : le dire plutôt que
d'inventer — savoir ce qu'on ne sait pas fait partie du travail.

## Méthode et honnêteté
Le chapitre donne des **ordres de grandeur**, pas des mesures. J'ai cherché, pour
chaque étape, une source publique qui donne une valeur *mesurée* ou *documentée par
le constructeur*. J'ai classé chaque ligne par **statut** :

- ✅ **Sourcé** : une source publique donne une valeur mesurée cohérente.
- ⚠️ **Partiel** : un ordre de grandeur est documenté, mais pas une mesure précise et
  indépendante (elle dépend du matériel exact ou du protocole).
- ❌ **Introuvable / non universel** : aucune valeur mesurée unique n'existe, parce que
  la valeur dépend entièrement de l'application ou n'est pas publiée.

> Note d'intégrité : je n'ai pas inventé de chiffres ni de liens. Les sources ci-dessous
> sont réelles et connues du domaine, mais **ouvre chacune pour confirmer la valeur
> exacte avant remise** — certains liens constructeur changent d'adresse avec le temps.

## Tableau

| # | Étape (chapitre) | Valeur du chapitre | Valeur trouvée dans une source | Statut | Source |
|---|------------------|--------------------|--------------------------------|--------|--------|
| 1 | Les capteurs mesurent le mouvement | 1–2 ms | IMU échantillonné à ~1000 Hz → ~1 ms entre deux mesures | ✅ Sourcé | [1], [5] |
| 2 | Le système transmet la mesure | 1–3 ms | Transfert USB HID historiquement à 1 ms (polling 1000 Hz) ; latence exacte dépend du bus | ⚠️ Partiel | [1] |
| 3 | L'application décide et dessine | 5–11 ms | **Pas de valeur mesurée universelle** : dépend entièrement de la scène, du GPU et du jeu | ❌ Non universel | [1], [2] |
| 4 | Le compositeur assemble | 1–2 ms | Le compositeur (TimeWarp/ATW) s'exécute juste avant le v-sync ; coût GPU documenté « faible » mais chiffre exact variable | ⚠️ Partiel | [4] |
| 5 | L'écran affiche la ligne | 2–5 ms | Écran « basse persistance » : illumination ~2 ms ; temps de réponse pixel OLED < 1 ms (LCD bien plus lent) | ✅ Sourcé | [3] |

## Ce que je n'ai pas pu sourcer précisément (et pourquoi)
- **Étape 2 (transmission)** : on trouve l'ordre de grandeur du polling USB (~1 ms), mais
  une *mesure indépendante* de la latence de transmission d'un casque précis n'est pas
  publiée par les constructeurs. → honnêtement : **valeur non mesurable publiquement**.
- **Étape 3 (rendu de l'application)** : ce n'est pas une constante mesurable une fois
  pour toutes ; c'est *ma* charge de travail. La « valeur » n'existe que pour un
  programme donné, sur un GPU donné. → **pas de valeur universelle** : à mesurer soi-même
  (voir l'exercice 6, « la pire image »).
- **Étape 4 (compositeur)** : le principe est documenté par Meta, mais le coût en ms
  exact n'est pas donné comme une mesure chiffrée stable. → **ordre de grandeur seulement**.

## Sources
[1] **John Carmack**, *« Latency Mitigation Strategies »*, 2013. Décompose la chaîne de
latence : échantillonnage du capteur, transfert USB, traitement/ rendu, balayage de
l'écran, temps de commutation des pixels. → étapes 1, 2, 3.

[2] **Michael Abrash**, *« Latency: the sine qua non of AR and VR »*, blog *Ramblings in
Valve Time*, 2012. Établit le seuil « mouvement → photon » d'environ 20 ms. → cadre
général + étape 3.

[3] **Michael Abrash**, *« Down the VR rabbit hole: Fixing Judder »*, *Ramblings in Valve
Time*, 2013. Écrans à basse persistance, illumination de l'ordre de ~2 ms. → étape 5.

[4] **Meta / Oculus Developer Documentation**, *« Asynchronous TimeWarp (ATW) »* et pages
sur le compositeur (developers.meta.com, anciennement developer.oculus.com). → étape 4.

[5] **Fiche technique d'un IMU MEMS grand public** (ex. InvenSense/TDK, Bosch Sensortec) :
fréquence de sortie (ODR) jusqu'à ≥ 1000 Hz, soit un échantillon ~toutes les 1 ms.
→ étape 1.

### Pistes à vérifier pour aller plus loin (mesures académiques de latence M2P)
Des travaux universitaires mesurent la latence « mouvement → photon » de bout en bout
(par ex. recherches de Raaen & Kjellmo sur la mesure de latence en VR, ~2015). À ouvrir
et vérifier si l'on veut une **mesure chiffrée end-to-end** plutôt que par étape.

## Conclusion
Sur les cinq étapes, **deux sont solidement sourçables** (capteur, affichage), **deux ne
le sont que partiellement** (transmission, compositeur — ordres de grandeur documentés,
pas de mesure précise publiée), et **une n'a pas de valeur mesurée universelle** (le
rendu, qui dépend de l'application). Conformément à l'énoncé, je le dis explicitement
plutôt que d'inventer des chiffres.

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

## Tableau

| # | Étape (chapitre) | Valeur du chapitre | Valeur trouvée dans une source | Statut | Source |
|---|------------------|--------------------|--------------------------------|--------|--------|
| 1 | Les capteurs mesurent le mouvement | 1–2 ms | IMU MEMS échantillonné à ≥ 1000 Hz (jusqu'à 1600 Hz accéléro / 3200 Hz gyro sur le Bosch BMI160) → **< 1 ms** entre deux mesures | ✅ Sourcé | [5], [1] |
| 2 | Le système transmet la mesure | 1–3 ms | Transfert USB HID historiquement à 1 ms (polling 1000 Hz) ; la latence exacte dépend du bus et n'est pas publiée par les constructeurs de casques | ⚠️ Partiel | [1] |
| 3 | L'application décide et dessine | 5–11 ms | **Pas de valeur mesurée universelle** : dépend entièrement de la scène, du GPU et du jeu | ❌ Non universel | [1], [2] |
| 4 | Le compositeur assemble | 1–2 ms | Le compositeur (Async TimeWarp) s'exécute à un instant fixe juste avant le v-sync pour livrer une latence d'orientation faible et constante ; coût en ms exact non chiffré publiquement | ⚠️ Partiel | [4] |
| 5 | L'écran affiche la ligne | 2–5 ms | Écran « basse persistance » : illumination de l'ordre de ~2 ms ; temps de réponse pixel OLED < 1 ms (LCD bien plus lent) | ✅ Sourcé | [3] |

## Ce que je n'ai pas pu sourcer précisément (et pourquoi)
- **Étape 2 (transmission)** : on trouve l'ordre de grandeur du polling USB (~1 ms), mais
  une *mesure indépendante* de la latence de transmission d'un casque précis n'est pas
  publiée par les constructeurs. → **valeur non mesurable publiquement**.
- **Étape 3 (rendu de l'application)** : ce n'est pas une constante mesurable une fois
  pour toutes ; c'est *ma* charge de travail. La « valeur » n'existe que pour un
  programme donné, sur un GPU donné. → **pas de valeur universelle** (à mesurer soi-même,
  cf. exercice 6 « la pire image »).
- **Étape 4 (compositeur)** : le principe et le *rôle* sont documentés par Meta, mais le
  coût en millisecondes exact n'est pas donné comme une mesure chiffrée stable. → **ordre
  de grandeur seulement**.

## Sources (URLs vérifiées)
[1] **John Carmack**, *« Latency Mitigation Strategies »*, 2013 — décompose la chaîne de
latence (capteur, transfert USB, traitement/rendu, balayage écran, commutation des
pixels). Publié à l'origine sur AltDevBlogADay (site fermé) ; copie intégrale fiable :
<https://danluu.com/latency-mitigation/>. → étapes 1, 2, 3.

[2] **Michael Abrash**, *« Latency – the sine qua non of AR and VR »*, blog *Ramblings in
Valve Time*, 29 déc. 2012 — établit le seuil « mouvement → photon » d'environ 20 ms :
<http://blogs.valvesoftware.com/abrash/latency-the-sine-qua-non-of-ar-and-vr/>. →
cadre général + étape 3.

[3] **Michael Abrash**, *« Down the VR rabbit hole: Fixing judder »*, *Ramblings in Valve
Time*, 26 juil. 2013 — écrans à basse persistance, illumination ~2 ms :
<http://blogs.valvesoftware.com/abrash/down-the-vr-rabbit-hole-fixing-judder/>. →
étape 5.

[4] **Meta / Oculus Developer Documentation**, *« Asynchronous TimeWarp (ATW) »* :
<https://developer.oculus.com/documentation/native/android/mobile-timewarp-overview/>
et l'article détaillé *« Asynchronous Timewarp Examined »* :
<https://developers.meta.com/horizon/blog/asynchronous-timewarp-examined/>. → étape 4.

[5] **Bosch Sensortec**, *fiche technique de l'IMU BMI160* (ODR jusqu'à 1600 Hz accéléro /
3200 Hz gyro → échantillon en moins d'1 ms) :
<https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi160-ds000.pdf>.
→ étape 1.

[6] **K. Raaen & I. Kjellmo**, *« Measuring Latency in Virtual Reality Systems »*, ICEC
2015, LNCS vol. 9353, p. 457–462 — mesure physique de bout en bout de la latence
« mouvement → photon » :
<https://link.springer.com/chapter/10.1007/978-3-319-24589-8_40>
(PDF : <https://www.researchgate.net/publication/300253386_Measuring_Latency_in_Virtual_Reality_Systems>).
→ mesure end-to-end, en complément des valeurs par étape.

## Conclusion
Sur les cinq étapes, **deux sont solidement sourçables** (capteur [5], affichage [3]),
**deux ne le sont que partiellement** (transmission, compositeur — ordres de grandeur
documentés, pas de mesure précise publiée), et **une n'a pas de valeur mesurée
universelle** (le rendu, qui dépend de l'application). Conformément à l'énoncé, je le dis
explicitement plutôt que d'inventer des chiffres. La source [6] fournit, elle, une mesure
*globale* (bout en bout) qui recoupe le budget des ~20 ms.

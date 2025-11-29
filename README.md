# Projet Télémétrie Médicale

## Description
Ce projet consiste en un système de **télémétrie médicale** utilisant un **ESP32** et un **capteur de pouls** pour collecter, afficher et analyser des données biométriques en temps réel.  
Le projet est développé et simulé sur **Wokwi**.

## Fonctionnalités
- Lecture des données du capteur de pouls
- Affichage sur console ou écran simulé
- Alertes en cas de dépassement de seuils
- Simulation complète sur Wokwi pour test du système

## Contenu du dépôt
- `sketch.ino` : code principal Arduino/ESP32
- `pulsesensor.chip.c` et `pulsesensor.chip.json` : fichiers capteur Wokwi
- `diagram.json` : schéma de connexion du circuit
- `libraries.txt` : bibliothèques utilisées
- `wokwi-project.txt` : configuration du projet Wokwi

## Simulation
Pour lancer la simulation :  
1. Aller sur [Wokwi](https://wokwi.com/)  
2. Importer le fichier `wokwi-project.txt` ou `diagram.json`  
3. Exécuter la simulation pour visualiser le fonctionnement du système

## Matériel utilisé
- ESP32 DevKit
- Capteur de pouls (Pulse Sensor)
- Câblage virtuel via Wokwi





# Scan Image Extractor Classifier

This project contains a scan image extractor and classifier. The goal of the project is to realize an original method for automatic identification of these icons and to evaluate the performances of the proposed method. 

The database was obtained by asking 35 volunteer scripters to reproduce each of the 14 icons, in 3 different sizes (large, medium, small). It is a set of 14 icons which can be used by emergency services in a crisis situation.

## Scan image example
![Picture1](https://github.com/SeanZheng21/Scan-Image-Classifier/blob/master/screenshots/Picture1.png)

## Tokens
![Icons1](https://github.com/SeanZheng21/Scan-Image-Classifier/blob/master/screenshots/icons1.png)
![Icons2](https://github.com/SeanZheng21/Scan-Image-Classifier/blob/master/screenshots/icons2.png)

## Classification Results
![Results](https://github.com/SeanZheng21/Scan-Image-Classifier/blob/master/screenshots/results.png)

## Workflow
The steps of the project correspond to these 4 parts:
1. Pre-processing and image processing

* Constitute a ground-truth from the provided data.
* Build a data base containing isolated drawings and associated information: icon, size, scripter, form id, form location.

2. Feature Extraction

* Choose and extract features from each drawing
* Several types of characteristics will be extracted from the drawings. Some of them will be mandatory and you will choose other characteristics that seem meaningful. You will use the WEKA software to display the extracted features, to help selecting the set of most relevant features.

3. Classification

* Develop a classifier based on the chosen set of features.

4. Evaluation

* Evaluate the performances of the developed classifier.
* Analyze obtained results


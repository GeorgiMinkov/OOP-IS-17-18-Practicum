Имате следната йерархия:

Melody - което представлява мелодия, която пази в себе си само име     string name;
Song - песен която имплементира Melody =-     float duration; string author;
Mix - имплементира Melody, с данни : vector<Melody*> tree; string frontCover;


реализирайте сериализация и десериализация. В клас Микс имайте функция за добавяне на песен или микс

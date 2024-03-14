#include <M5EPD.h>
//tho
M5EPD_Canvas canvas(&M5.EPD);

const int NUM_OPTIONS = 3;
const char *options[NUM_OPTIONS] = {"BT", "manuel", "Musique"};
const int buttonY = 700;
const int buttonWidth = 120;
const int buttonHeight = 60;
const int optionSpacing = 40; // Espacement entre les options

bool optionSelected = false;

void drawMenu() {
    canvas.fillCanvas(0);
    canvas.setTextSize(3);
    int totalWidth = NUM_OPTIONS * buttonWidth + (NUM_OPTIONS - 1) * optionSpacing;
    int startX = (540 - totalWidth) / 2;
    int startY = (960 - buttonHeight) / 2; // Position verticale centrale
    for (int i = 0; i < NUM_OPTIONS; i++) {
        canvas.drawRect(startX + i * (buttonWidth + optionSpacing), startY, buttonWidth, buttonHeight, 15);
        canvas.drawString(options[i], startX + i * (buttonWidth + optionSpacing) + 10, startY + 10);
    }
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void drawBackButton() {
    canvas.drawRect(20, 20, buttonWidth, buttonHeight, 15);
    canvas.setTextSize(2);
    canvas.drawString("Retour", 30, 30);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void performAction(const char *option) {
    canvas.fillCanvas(0);
    canvas.setTextSize(5);
    if (strcmp(option, "BT") == 0) {
        canvas.drawString("Thomas", 100, 400);
    } else if (strcmp(option, "manuel") == 0) {
        canvas.drawString("OK", 200, 400);
    } else if (strcmp(option, "Musique") == 0) {
        // Ajoutez ici le code pour l'action correspondant à "Musique"
    }
    drawBackButton();
}

void setup() {
    M5.begin();
    M5.EPD.SetRotation(180); // Réglez la rotation de l'écran sur 180 degrés
    M5.TP.SetRotation(180);  // Réglez la rotation du toucher sur 180 degrés
    M5.EPD.Clear(true);
    canvas.createCanvas(540, 960);
    drawMenu();
}


void loop() {
    if (M5.TP.available()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                int touchX = FingerItem.x;
                int touchY = FingerItem.y;
                if (!optionSelected) {
                    int totalWidth = NUM_OPTIONS * buttonWidth + (NUM_OPTIONS - 1) * optionSpacing;
                    int startX = (540 - totalWidth) / 2;
                    int startY = (960 - buttonHeight) / 2; // Position verticale centrale
                    for (int j = 0; j < NUM_OPTIONS; j++) {
                        int buttonX = startX + j * (buttonWidth + optionSpacing);
                        int buttonY = startY;
                        if (touchX >= buttonX && touchX <= buttonX + buttonWidth &&
                            touchY >= buttonY && touchY <= buttonY + buttonHeight) {
                            // Action correspondant à l'option j
                            Serial.printf("Option sélectionnée: %s\n", options[j]);
                            performAction(options[j]);
                            optionSelected = true;
                        }
                    }
                } else {
                    if (touchX >= 20 && touchX <= 20 + buttonWidth &&
                        touchY >= 20 && touchY <= 20 + buttonHeight) {
                        // Bouton "retour" pressé, réafficher le menu
                        drawMenu();
                        optionSelected = false;
                    }
                }
            }
        }
    }
}

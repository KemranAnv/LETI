package org.auth_app.ui;

public class MainApplication {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {
            UserInterface ui = new UserInterface();
            ui.createAndShowGUI();
        });
    }
}

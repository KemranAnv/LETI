package org.auth_app.ui;

import org.auth_app.database.UserDAO;
import org.auth_app.model.EntityUser;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Random;

public class UserInterface {
    private JFrame frame;
    private JTable table;
    private DefaultTableModel tableModel;

    public void createAndShowGUI() {
        frame = new JFrame("Authentication App");
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

        tableModel = new DefaultTableModel();
        tableModel.addColumn("User");
        tableModel.addColumn("Email");
        tableModel.addColumn("Password");

        UserDAO userService = new UserDAO();
        java.util.List<EntityUser> users = userService.findAll();

        for (int i = 0; i < users.size(); i++) {
            EntityUser user = users.get(i);
            String[] rowData = {user.getUser(), user.getEmail(), user.getPassword()};
            tableModel.addRow(rowData);
            System.out.println(users.get(i).getUser() + " " + users.get(i).getEmail());
        }

        table = new JTable(tableModel);

        JScrollPane scrollPane = new JScrollPane(table);
        frame.getContentPane().add(scrollPane, BorderLayout.CENTER);

        JButton addButton = new JButton("Добавить");
        JButton editButton = new JButton("Редактировать");
        JButton deleteButton = new JButton("Удалить");
        JButton exitButton = new JButton("Выход");

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(addButton);
        buttonPanel.add(editButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(exitButton);

        frame.getContentPane().add(buttonPanel, BorderLayout.SOUTH);

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addRow();
            }
        });

        editButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                editRow();
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                deleteRow();
            }
        });

        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                confirmExit();
            }
        });

        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                confirmExit();
            }
        });

        // Таймер для обновления паролей каждые 5 секунд
        Timer timer = new Timer(5000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updatePasswords();
            }
        });
        timer.start();

        frame.setSize(600, 400);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }


    private void addRow() {
        String user = JOptionPane.showInputDialog(frame, "Введите пользователя:", "Добавление", JOptionPane.PLAIN_MESSAGE);
        String email = JOptionPane.showInputDialog(frame, "Введите email:", "Добавление", JOptionPane.PLAIN_MESSAGE);
        String password = JOptionPane.showInputDialog(frame, "Введите пароль:", "Добавление", JOptionPane.PLAIN_MESSAGE);

        if (user != null && email != null && password != null) {
            String[] rowData = {user, email, password};
            tableModel.addRow(rowData);
        }
    }

    private void editRow() {
        int selectedRow = table.getSelectedRow();

        if (selectedRow != -1) {
            String user = JOptionPane.showInputDialog(frame, "Введите пользователя:", "Редактирование", JOptionPane.PLAIN_MESSAGE);
            String email = JOptionPane.showInputDialog(frame, "Введите email:", "Редактирование", JOptionPane.PLAIN_MESSAGE);
            String password = JOptionPane.showInputDialog(frame, "Введите пароль:", "Редактирование", JOptionPane.PLAIN_MESSAGE);

            if (user != null && email != null && password != null) {
                tableModel.setValueAt(user, selectedRow, 0);
                tableModel.setValueAt(email, selectedRow, 1);
                tableModel.setValueAt(password, selectedRow, 2);
            }
        } else {
            JOptionPane.showMessageDialog(frame, "Выберите строку для редактирования.", "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void deleteRow() {
        int selectedRow = table.getSelectedRow();

        if (selectedRow != -1) {
            int confirm = JOptionPane.showConfirmDialog(frame, "Вы уверены, что хотите удалить эту строку?", "Удаление", JOptionPane.YES_NO_OPTION);

            if (confirm == JOptionPane.YES_OPTION) {
                tableModel.removeRow(selectedRow);
            }
        } else {
            JOptionPane.showMessageDialog(frame, "Выберите строку для удаления.", "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void updatePasswords() {
        // Генерация новых паролей и обновление таблицы
        for (int i = 0; i < tableModel.getRowCount(); i++) {
            String newPassword = generateRandomPassword();
            tableModel.setValueAt(newPassword, i, 2);
        }
    }

    private String generateRandomPassword() {
        // Генерация случайного пароля
        Random random = new Random();
        StringBuilder password = new StringBuilder();
        for (int i = 0; i < 6; i++) {
            password.append(random.nextInt(9) + 1);
        }
        return password.toString();
    }

    private void confirmExit() {
        int confirm = JOptionPane.showConfirmDialog(frame, "Вы точно хотите выйти?", "Выход", JOptionPane.YES_NO_OPTION);

        if (confirm == JOptionPane.YES_OPTION) {
            System.exit(0);
        }
    }

    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {
            UserInterface ui = new UserInterface();
            ui.createAndShowGUI();
        });
    }
}

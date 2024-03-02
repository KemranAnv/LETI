package org.auth_app.server;

import org.auth_app.database.HibernateUtil;
import org.auth_app.database.UserDAO;
import org.auth_app.model.EntityUser;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.hibernate.cfg.Environment;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.Properties;

public class Server {
    private static final int PORT = 12345;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Сервер запущен. Ожидание подключений...");


                //Socket clientSocket = serverSocket.accept();
                //System.out.println("Подключен клиент: " + clientSocket.getInetAddress());

                // Обработка подключения клиента - ваш код здесь
                UserDAO userService = new UserDAO();
                List<EntityUser> users = userService.findAll();
                for (int i = 0; i < users.size(); i++)
                    System.out.println(users.get(i).getUser() + " " + users.get(i).getEmail());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

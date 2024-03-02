package org.auth_app.database;

import org.auth_app.model.EntityUser;

import java.util.List;

public class UserDAO  {
    public List<EntityUser> findAll() {
        List<EntityUser> users = (List<EntityUser>)  HibernateSessionFactoryUtil.getSessionFactory().openSession().createQuery("FROM entityuser").list();
        return users;
    }
}

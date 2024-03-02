package org.auth_app.database;

import org.auth_app.model.Email;

public class EmailDAO extends GenericDAO<Email, String> {

    public EmailDAO() {
        super(Email.class);
    }
}

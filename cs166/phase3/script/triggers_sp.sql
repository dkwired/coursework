CREATE LANGUAGE plpgsql;

DROP TRIGGER moveDeletedUser ON users;
DROP FUNCTION moveDeletedUser();

CREATE FUNCTION moveDeletedUser() RETURNS trigger AS $$
    BEGIN
       DELETE FROM follow WHERE user_id_to=OLD.user_id;
       DELETE FROM follow WHERE user_id_from=OLD.user_id;
       INSERT INTO users_archive VALUES(OLD.user_id, OLD.password, Old.first_name, Old.middle_name, Old.last_name, Old.e_mail, Old.street1, Old.street2, Old.state, Old.country, Old.zipcode, Old.balance);
       RETURN OLD;
    END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER moveDeletedUser
BEFORE DELETE ON users
FOR EACH ROW
EXECUTE PROCEDURE moveDeletedUser();

DROP TRIGGER moveDeletedComment ON comment;
DROP FUNCTION moveDeletedComment();

CREATE FUNCTION moveDeletedComment() RETURNS trigger AS $$
    BEGIN
       INSERT INTO comment_archive VALUES(OLD.comment_id, OLD.user_id, OLD.video_id, OLD.comment_time, OLD.content);
       RETURN OLD;
    END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER moveDeletedComment
BEFORE DELETE ON comment
FOR EACH ROW
EXECUTE PROCEDURE moveDeletedComment();

CREATE TABLE `buksydb`.`user` (
  `id_user` INT NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(32) NULL,
  `password` VARCHAR(32) NULL,
  `first_name` VARCHAR(32) NULL,
  `last_name` VARCHAR(32) NULL,
  `email` VARCHAR(32) NULL,
  `active` VARCHAR(45) NULL DEFAULT 0,
  PRIMARY KEY (`id_user`));

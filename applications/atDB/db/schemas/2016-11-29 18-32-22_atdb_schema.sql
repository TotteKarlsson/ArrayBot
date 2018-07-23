/*
SQLyog Ultimate v12.18 (64 bit)
MySQL - 5.7.15-log : Database - atdb
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`atdb` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `atdb`;

/*Table structure for table `block` */

DROP TABLE IF EXISTS `block`;

CREATE TABLE `block` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `process_id` int(11) DEFAULT NULL COMMENT 'This ID relates a block with a specimen process_id in the  specimen table',
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_by` int(11) NOT NULL,
  `modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `status` smallint(11) NOT NULL DEFAULT '0',
  `label` varchar(255) NOT NULL DEFAULT 'XXXXXX',
  `serial` smallint(5) unsigned NOT NULL COMMENT 'The serial starts at 1 and is related to the process_id',
  PRIMARY KEY (`id`),
  KEY `block_ibfk_1` (`created_by`),
  KEY `process_id` (`process_id`),
  KEY `status` (`status`),
  CONSTRAINT `block_ibfk_1` FOREIGN KEY (`created_by`) REFERENCES `user` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `block_ibfk_2` FOREIGN KEY (`process_id`) REFERENCES `specimen` (`process_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `block_ibfk_3` FOREIGN KEY (`status`) REFERENCES `blockstatus` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `block_note` */

DROP TABLE IF EXISTS `block_note`;

CREATE TABLE `block_note` (
  `block_id` int(11) DEFAULT NULL,
  `note_id` int(11) DEFAULT NULL,
  KEY `block_id` (`block_id`),
  KEY `note_id` (`note_id`),
  CONSTRAINT `block_note_ibfk_1` FOREIGN KEY (`block_id`) REFERENCES `block` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `block_note_ibfk_3` FOREIGN KEY (`note_id`) REFERENCES `note` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `blockstatus` */

DROP TABLE IF EXISTS `blockstatus`;

CREATE TABLE `blockstatus` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `status` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

/*Table structure for table `cleancsbatch` */

DROP TABLE IF EXISTS `cleancsbatch`;

CREATE TABLE `cleancsbatch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL,
  `freshCSbatch` int(11) NOT NULL,
  `cleanedCSbatch` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `freshBatch` (`freshCSbatch`),
  CONSTRAINT `freshBatch` FOREIGN KEY (`freshCSbatch`) REFERENCES `freshcsbatch` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `coverslip` */

DROP TABLE IF EXISTS `coverslip`;

CREATE TABLE `coverslip` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` int(11) NOT NULL COMMENT 'The coverslips state',
  `type` int(11) NOT NULL COMMENT 'Type of cs',
  `notes` text,
  `freshCSBatch` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `status` (`status`),
  KEY `type` (`type`),
  CONSTRAINT `coverslip_ibfk_1` FOREIGN KEY (`status`) REFERENCES `coverslipstatus` (`id`),
  CONSTRAINT `coverslip_ibfk_2` FOREIGN KEY (`type`) REFERENCES `coversliptype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1606 DEFAULT CHARSET=utf8;

/*Table structure for table `coverslipdustassay` */

DROP TABLE IF EXISTS `coverslipdustassay`;

CREATE TABLE `coverslipdustassay` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime DEFAULT CURRENT_TIMESTAMP,
  `coverslip_id` int(11) NOT NULL,
  `background_image` varchar(36) DEFAULT NULL,
  `coverslip_image` varchar(36) DEFAULT NULL,
  `result_image` varchar(36) DEFAULT NULL,
  `coverslip_status` int(11) NOT NULL COMMENT 'Status of coverslip at time of control',
  `note` text,
  PRIMARY KEY (`id`),
  KEY `coverslip_id` (`coverslip_id`),
  KEY `coverslip_status` (`coverslip_status`),
  CONSTRAINT `coverslipdustassay_ibfk_1` FOREIGN KEY (`coverslip_id`) REFERENCES `coverslip` (`id`),
  CONSTRAINT `coverslipdustassay_ibfk_2` FOREIGN KEY (`coverslip_status`) REFERENCES `coverslipstatus` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `coverslipstatus` */

DROP TABLE IF EXISTS `coverslipstatus`;

CREATE TABLE `coverslipstatus` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` varchar(255) NOT NULL,
  `note` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*Table structure for table `coversliptype` */

DROP TABLE IF EXISTS `coversliptype`;

CREATE TABLE `coversliptype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(255) NOT NULL,
  `note` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

/*Table structure for table `cryoprotection` */

DROP TABLE IF EXISTS `cryoprotection`;

CREATE TABLE `cryoprotection` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `cryoprotection_ibfk_1` (`document_id`),
  CONSTRAINT `cryoprotection_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `document` */

DROP TABLE IF EXISTS `document`;

CREATE TABLE `document` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `document_name` varchar(255) NOT NULL,
  `document` longblob,
  `type` varchar(16) DEFAULT NULL COMMENT 'document extension',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `embedding` */

DROP TABLE IF EXISTS `embedding`;

CREATE TABLE `embedding` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `embedding_ibfk_1` (`document_id`),
  CONSTRAINT `embedding_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

/*Table structure for table `fixative` */

DROP TABLE IF EXISTS `fixative`;

CREATE TABLE `fixative` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fixative_ibfk_1` (`document_id`),
  CONSTRAINT `fixative_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `fixmethod` */

DROP TABLE IF EXISTS `fixmethod`;

CREATE TABLE `fixmethod` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fixmethod_ibfk_1` (`document_id`),
  CONSTRAINT `fixmethod_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `freezeprotocol` */

DROP TABLE IF EXISTS `freezeprotocol`;

CREATE TABLE `freezeprotocol` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(128) NOT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `freezeprotocol_ibfk_1` (`document_id`),
  CONSTRAINT `freezeprotocol_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*Table structure for table `freshcsbatch` */

DROP TABLE IF EXISTS `freshcsbatch`;

CREATE TABLE `freshcsbatch` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date_created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `count` int(11) DEFAULT NULL,
  `batchcode` varchar(9) NOT NULL DEFAULT '0000000',
  `type` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `type` (`type`),
  CONSTRAINT `freshcsbatch_ibfk_1` FOREIGN KEY (`type`) REFERENCES `coversliptype` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8;

/*Table structure for table `image` */

DROP TABLE IF EXISTS `image`;

CREATE TABLE `image` (
  `id` varchar(36) NOT NULL,
  `created` datetime DEFAULT CURRENT_TIMESTAMP,
  `filename` varchar(255) NOT NULL,
  `fileextension` varchar(16) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `infiltration` */

DROP TABLE IF EXISTS `infiltration`;

CREATE TABLE `infiltration` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `infiltration_ibfk_1` (`document_id`),
  CONSTRAINT `infiltration_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

/*Table structure for table `note` */

DROP TABLE IF EXISTS `note`;

CREATE TABLE `note` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `note` mediumtext NOT NULL,
  `created_on` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_by` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `postfix` */

DROP TABLE IF EXISTS `postfix`;

CREATE TABLE `postfix` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `postfix_ibfk_1` (`document_id`),
  CONSTRAINT `postfix_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

/*Table structure for table `preprocesstreatment` */

DROP TABLE IF EXISTS `preprocesstreatment`;

CREATE TABLE `preprocesstreatment` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `preprocesstreatment_ibfk_1` (`document_id`),
  CONSTRAINT `preprocesstreatment_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;

/*Table structure for table `ribbon` */

DROP TABLE IF EXISTS `ribbon`;

CREATE TABLE `ribbon` (
  `id` varchar(36) NOT NULL,
  `status` int(11) NOT NULL DEFAULT '0',
  `block_id` int(11) NOT NULL DEFAULT '-1',
  `cutting_order` int(11) NOT NULL DEFAULT '-1',
  `nr_of_sections` smallint(6) DEFAULT '0',
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `block_id` (`block_id`),
  CONSTRAINT `ribbon_ibfk_1` FOREIGN KEY (`block_id`) REFERENCES `block` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `ribbon_note` */

DROP TABLE IF EXISTS `ribbon_note`;

CREATE TABLE `ribbon_note` (
  `ribbon_id` varchar(36) DEFAULT NULL,
  `note_id` int(11) DEFAULT NULL,
  KEY `ribbon_id` (`ribbon_id`),
  KEY `note_id` (`note_id`),
  CONSTRAINT `ribbon_note_ibfk_1` FOREIGN KEY (`ribbon_id`) REFERENCES `ribbon` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ribbon_note_ibfk_2` FOREIGN KEY (`note_id`) REFERENCES `note` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `specie` */

DROP TABLE IF EXISTS `specie`;

CREATE TABLE `specie` (
  `id` smallint(6) NOT NULL,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `specimen` */

DROP TABLE IF EXISTS `specimen`;

CREATE TABLE `specimen` (
  `process_id` int(11) NOT NULL AUTO_INCREMENT,
  `specimen_id` varchar(255) NOT NULL,
  `specie` smallint(11) DEFAULT NULL,
  `additional_identifier` varchar(255) DEFAULT NULL,
  `age` varchar(255) DEFAULT NULL,
  `lims_number` int(11) DEFAULT NULL,
  `death_date` date DEFAULT NULL,
  `preprocess_treatment` smallint(6) DEFAULT '0',
  `fixative` smallint(6) DEFAULT '0',
  `fixation_method` smallint(6) DEFAULT '0',
  `brain_region_dissection` varchar(255) DEFAULT NULL,
  `postfix_protocol` smallint(4) DEFAULT NULL,
  `date_received` date DEFAULT NULL,
  `date_embedded` date DEFAULT NULL,
  `cryoprotection_protocol` smallint(4) DEFAULT '0',
  `freezing_protocol` smallint(4) DEFAULT '0',
  `substitution_protocol` smallint(4) DEFAULT '0',
  `infiltration_protocol` smallint(4) DEFAULT '0',
  `embedding_protocol` smallint(4) DEFAULT '0',
  PRIMARY KEY (`process_id`),
  KEY `fixation_method` (`fixation_method`),
  KEY `fixative` (`fixative`),
  KEY `postfix_protocol` (`postfix_protocol`),
  KEY `cryoprotection_protocol` (`cryoprotection_protocol`),
  KEY `freezing_protocol` (`freezing_protocol`),
  KEY `substitution_protocol` (`substitution_protocol`),
  KEY `infiltration_protocol` (`infiltration_protocol`),
  KEY `embedding_protocol` (`embedding_protocol`),
  KEY `preprocess_treatment` (`preprocess_treatment`),
  KEY `species` (`specie`),
  CONSTRAINT `specimen_ibfk_1` FOREIGN KEY (`fixation_method`) REFERENCES `fixmethod` (`id`),
  CONSTRAINT `specimen_ibfk_10` FOREIGN KEY (`specie`) REFERENCES `specie` (`id`),
  CONSTRAINT `specimen_ibfk_2` FOREIGN KEY (`fixative`) REFERENCES `fixative` (`id`),
  CONSTRAINT `specimen_ibfk_3` FOREIGN KEY (`postfix_protocol`) REFERENCES `postfix` (`id`),
  CONSTRAINT `specimen_ibfk_4` FOREIGN KEY (`cryoprotection_protocol`) REFERENCES `cryoprotection` (`id`),
  CONSTRAINT `specimen_ibfk_5` FOREIGN KEY (`freezing_protocol`) REFERENCES `freezeprotocol` (`id`),
  CONSTRAINT `specimen_ibfk_6` FOREIGN KEY (`substitution_protocol`) REFERENCES `substitution` (`id`),
  CONSTRAINT `specimen_ibfk_7` FOREIGN KEY (`infiltration_protocol`) REFERENCES `infiltration` (`id`),
  CONSTRAINT `specimen_ibfk_8` FOREIGN KEY (`embedding_protocol`) REFERENCES `embedding` (`id`),
  CONSTRAINT `specimen_ibfk_9` FOREIGN KEY (`preprocess_treatment`) REFERENCES `preprocesstreatment` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=846 DEFAULT CHARSET=utf8;

/*Table structure for table `substitution` */

DROP TABLE IF EXISTS `substitution`;

CREATE TABLE `substitution` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL COMMENT 'Reference to documents able',
  PRIMARY KEY (`id`),
  KEY `substitution_ibfk_1` (`document_id`),
  CONSTRAINT `substitution_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `document` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/*Table structure for table `user` */

DROP TABLE IF EXISTS `user`;

CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(255) NOT NULL,
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_name` (`user_name`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

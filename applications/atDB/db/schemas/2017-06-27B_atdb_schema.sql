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

/*Table structure for table `block_note` */

DROP TABLE IF EXISTS `block_note`;

CREATE TABLE `block_note` (
  `block_id` int(11) DEFAULT NULL,
  `note_id` int(11) DEFAULT NULL,
  KEY `block_id` (`block_id`),
  KEY `note_id` (`note_id`),
  CONSTRAINT `block_note_ibfk_1` FOREIGN KEY (`block_id`) REFERENCES `blocks` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `block_note_ibfk_3` FOREIGN KEY (`note_id`) REFERENCES `notes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `blocks` */

DROP TABLE IF EXISTS `blocks`;

CREATE TABLE `blocks` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `specimen_id` int(11) DEFAULT NULL,
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `status` smallint(11) NOT NULL DEFAULT '0',
  `created_by` int(11) NOT NULL,
  `modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `label` varchar(255) NOT NULL DEFAULT 'XXXXXX',
  `serial` smallint(5) unsigned NOT NULL COMMENT 'The serial starts at 1 and is related to the process_id',
  `date_embedded` date DEFAULT NULL,
  `preprocess_treatment_protocol` smallint(6) DEFAULT '0',
  `fixative_protocol` smallint(6) DEFAULT '0',
  `fixation_protocol` smallint(6) DEFAULT '0',
  `postfix_protocol` smallint(6) DEFAULT '0',
  `cryoprotection_protocol` smallint(6) DEFAULT '0',
  `freezing_protocol` smallint(6) DEFAULT '0',
  `substitution_protocol` smallint(6) DEFAULT '0',
  `infiltration_protocol` smallint(6) DEFAULT '0',
  `embedding_protocol` smallint(6) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `block_ibfk_1` (`created_by`),
  KEY `process_id` (`specimen_id`),
  KEY `status` (`status`),
  KEY `preprocess_treatment` (`preprocess_treatment_protocol`),
  KEY `fixative` (`fixative_protocol`),
  KEY `fixation_protocol` (`fixation_protocol`),
  KEY `postfix_protocol` (`postfix_protocol`),
  KEY `cryoprotection_protocol` (`cryoprotection_protocol`),
  KEY `embedding_protocol` (`embedding_protocol`),
  KEY `freezing_protocol` (`freezing_protocol`),
  KEY `infiltration_protocol` (`infiltration_protocol`),
  KEY `substitution_protocol` (`substitution_protocol`),
  CONSTRAINT `blocks_ibfk_1` FOREIGN KEY (`created_by`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `blocks_ibfk_10` FOREIGN KEY (`freezing_protocol`) REFERENCES `freezeprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_11` FOREIGN KEY (`infiltration_protocol`) REFERENCES `infiltrationprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_12` FOREIGN KEY (`substitution_protocol`) REFERENCES `substitutionprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_2` FOREIGN KEY (`specimen_id`) REFERENCES `specimens` (`specimen_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `blocks_ibfk_3` FOREIGN KEY (`status`) REFERENCES `blockstatuses` (`id`),
  CONSTRAINT `blocks_ibfk_4` FOREIGN KEY (`preprocess_treatment_protocol`) REFERENCES `preprocesstreatmentprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_5` FOREIGN KEY (`fixative_protocol`) REFERENCES `fixativeprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_6` FOREIGN KEY (`fixation_protocol`) REFERENCES `fixationprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_7` FOREIGN KEY (`postfix_protocol`) REFERENCES `postfixprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_8` FOREIGN KEY (`cryoprotection_protocol`) REFERENCES `cryoprotectionprotocols` (`id`),
  CONSTRAINT `blocks_ibfk_9` FOREIGN KEY (`embedding_protocol`) REFERENCES `embeddingprotocols` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=88 DEFAULT CHARSET=utf8;

/*Table structure for table `blockstatuses` */

DROP TABLE IF EXISTS `blockstatuses`;

CREATE TABLE `blockstatuses` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `status` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

/*Table structure for table `carboncoatedcsbatches` */

DROP TABLE IF EXISTS `carboncoatedcsbatches`;

CREATE TABLE `carboncoatedcsbatches` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date_created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `count` int(11) DEFAULT NULL,
  `user` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=82 DEFAULT CHARSET=utf8;

/*Table structure for table `case` */

DROP TABLE IF EXISTS `case`;

CREATE TABLE `case` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `animal_id` varchar(64) NOT NULL,
  `intake_date` datetime DEFAULT CURRENT_TIMESTAMP,
  `specie` smallint(6) NOT NULL,
  `entered_by` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `specie` (`specie`),
  KEY `entered_by` (`entered_by`),
  CONSTRAINT `case_ibfk_1` FOREIGN KEY (`specie`) REFERENCES `species` (`id`),
  CONSTRAINT `case_ibfk_2` FOREIGN KEY (`entered_by`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

/*Table structure for table `cleancsbatches` */

DROP TABLE IF EXISTS `cleancsbatches`;

CREATE TABLE `cleancsbatches` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `user` int(11) NOT NULL,
  `note` text,
  `count` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `user` (`user`),
  CONSTRAINT `cleancsbatches_ibfk_1` FOREIGN KEY (`user`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=80 DEFAULT CHARSET=utf8;

/*Table structure for table `coverslipdustassays` */

DROP TABLE IF EXISTS `coverslipdustassays`;

CREATE TABLE `coverslipdustassays` (
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
  CONSTRAINT `coverslipdustassays_ibfk_1` FOREIGN KEY (`coverslip_id`) REFERENCES `coverslips` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `coverslips` */

DROP TABLE IF EXISTS `coverslips`;

CREATE TABLE `coverslips` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` int(11) NOT NULL COMMENT 'The coverslips state',
  `type` int(11) NOT NULL COMMENT 'Type of cs',
  `notes` text,
  `freshCSBatch` int(11) NOT NULL COMMENT 'Typcially a 100 count box',
  `cleanCSBatch` int(11) DEFAULT NULL,
  `carboncoatbatch` int(11) DEFAULT NULL,
  `from_lot` varchar(128) DEFAULT NULL COMMENT 'Coverslip LOT',
  PRIMARY KEY (`id`),
  KEY `status` (`status`),
  KEY `type` (`type`),
  KEY `coverslip_ibfk_3` (`freshCSBatch`),
  KEY `cleanCSBatch` (`cleanCSBatch`),
  KEY `carboncoatbatch` (`carboncoatbatch`),
  CONSTRAINT `coverslips_ibfk_1` FOREIGN KEY (`status`) REFERENCES `coverslipstatuses` (`id`),
  CONSTRAINT `coverslips_ibfk_2` FOREIGN KEY (`type`) REFERENCES `coversliptypes` (`id`),
  CONSTRAINT `coverslips_ibfk_3` FOREIGN KEY (`freshCSBatch`) REFERENCES `freshcsbatches` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `coverslips_ibfk_4` FOREIGN KEY (`cleanCSBatch`) REFERENCES `cleancsbatches` (`id`),
  CONSTRAINT `coverslips_ibfk_5` FOREIGN KEY (`carboncoatbatch`) REFERENCES `carboncoatedcsbatches` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3306 DEFAULT CHARSET=utf8;

/*Table structure for table `coverslipstatuses` */

DROP TABLE IF EXISTS `coverslipstatuses`;

CREATE TABLE `coverslipstatuses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` varchar(255) NOT NULL,
  `note` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/*Table structure for table `coversliptypes` */

DROP TABLE IF EXISTS `coversliptypes`;

CREATE TABLE `coversliptypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(255) NOT NULL,
  `note` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

/*Table structure for table `cryoprotectionprotocols` */

DROP TABLE IF EXISTS `cryoprotectionprotocols`;

CREATE TABLE `cryoprotectionprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `cryoprotection_ibfk_1` (`document_id`),
  CONSTRAINT `cryoprotectionprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

/*Table structure for table `cultured_time_point` */

DROP TABLE IF EXISTS `cultured_time_point`;

CREATE TABLE `cultured_time_point` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `time_point` varchar(32) DEFAULT 'N/A',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `documents` */

DROP TABLE IF EXISTS `documents`;

CREATE TABLE `documents` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `document_name` varchar(255) NOT NULL,
  `document` longblob,
  `type` varchar(16) DEFAULT NULL COMMENT 'document extension',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `embeddingprotocols` */

DROP TABLE IF EXISTS `embeddingprotocols`;

CREATE TABLE `embeddingprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `embedding_ibfk_1` (`document_id`),
  CONSTRAINT `embeddingprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/*Table structure for table `fixationprotocols` */

DROP TABLE IF EXISTS `fixationprotocols`;

CREATE TABLE `fixationprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fixmethod_ibfk_1` (`document_id`),
  CONSTRAINT `fixationprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

/*Table structure for table `fixativeprotocols` */

DROP TABLE IF EXISTS `fixativeprotocols`;

CREATE TABLE `fixativeprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fixative_ibfk_1` (`document_id`),
  CONSTRAINT `fixativeprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

/*Table structure for table `freezeprotocols` */

DROP TABLE IF EXISTS `freezeprotocols`;

CREATE TABLE `freezeprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(128) NOT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `freezeprotocol_ibfk_1` (`document_id`),
  CONSTRAINT `freezeprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

/*Table structure for table `freshcsbatches` */

DROP TABLE IF EXISTS `freshcsbatches`;

CREATE TABLE `freshcsbatches` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date_created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `count` int(11) DEFAULT NULL COMMENT 'Typically 100',
  `type` int(11) NOT NULL,
  `lot_number` varchar(128) NOT NULL,
  `box_number` int(11) NOT NULL COMMENT 'Typically the box that holds 100 coverslips',
  PRIMARY KEY (`id`),
  KEY `type` (`type`),
  CONSTRAINT `freshcsbatches_ibfk_1` FOREIGN KEY (`type`) REFERENCES `coversliptypes` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=103 DEFAULT CHARSET=utf8;

/*Table structure for table `images` */

DROP TABLE IF EXISTS `images`;

CREATE TABLE `images` (
  `id` varchar(36) NOT NULL,
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `fileextension` varchar(16) DEFAULT NULL,
  `created_by` int(11) NOT NULL,
  `coverslip_id` int(11) NOT NULL DEFAULT '0' COMMENT 'For now, this is not enforced that it need to exist in the DB',
  `block_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `created_by` (`created_by`),
  CONSTRAINT `images_ibfk_1` FOREIGN KEY (`created_by`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `infiltrationprotocols` */

DROP TABLE IF EXISTS `infiltrationprotocols`;

CREATE TABLE `infiltrationprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `infiltration_ibfk_1` (`document_id`),
  CONSTRAINT `infiltrationprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

/*Table structure for table `modificationlog` */

DROP TABLE IF EXISTS `modificationlog`;

CREATE TABLE `modificationlog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime DEFAULT CURRENT_TIMESTAMP,
  `text` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `movies` */

DROP TABLE IF EXISTS `movies`;

CREATE TABLE `movies` (
  `id` varchar(36) NOT NULL,
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `fileextension` varchar(16) DEFAULT NULL,
  `created_by` int(11) NOT NULL,
  `coverslip_id` int(11) NOT NULL DEFAULT '0',
  `block_id` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `notes` */

DROP TABLE IF EXISTS `notes`;

CREATE TABLE `notes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `note` mediumtext NOT NULL,
  `created_on` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_by` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=52 DEFAULT CHARSET=utf8;

/*Table structure for table `postfixprotocols` */

DROP TABLE IF EXISTS `postfixprotocols`;

CREATE TABLE `postfixprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `postfix_ibfk_1` (`document_id`),
  CONSTRAINT `postfixprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;

/*Table structure for table `preprocesstreatmentprotocols` */

DROP TABLE IF EXISTS `preprocesstreatmentprotocols`;

CREATE TABLE `preprocesstreatmentprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `preprocesstreatment_ibfk_1` (`document_id`),
  CONSTRAINT `preprocesstreatmentprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;

/*Table structure for table `ribbon_note` */

DROP TABLE IF EXISTS `ribbon_note`;

CREATE TABLE `ribbon_note` (
  `ribbon_id` varchar(36) DEFAULT NULL,
  `note_id` int(11) DEFAULT NULL,
  KEY `ribbon_id` (`ribbon_id`),
  KEY `note_id` (`note_id`),
  CONSTRAINT `ribbon_note_ibfk_1` FOREIGN KEY (`ribbon_id`) REFERENCES `ribbons` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `ribbon_note_ibfk_2` FOREIGN KEY (`note_id`) REFERENCES `notes` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `ribbons` */

DROP TABLE IF EXISTS `ribbons`;

CREATE TABLE `ribbons` (
  `id` varchar(36) NOT NULL,
  `status` int(11) NOT NULL DEFAULT '1',
  `block_id` int(11) NOT NULL DEFAULT '-1',
  `cutting_order` int(11) NOT NULL DEFAULT '-1',
  `nr_of_sections` smallint(6) DEFAULT '0',
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_by` int(11) NOT NULL,
  `coverslip_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `block_id` (`block_id`),
  KEY `created_by` (`created_by`),
  KEY `coverslip_id` (`coverslip_id`),
  KEY `status` (`status`),
  CONSTRAINT `ribbons_ibfk_1` FOREIGN KEY (`block_id`) REFERENCES `blocks` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `ribbons_ibfk_2` FOREIGN KEY (`created_by`) REFERENCES `users` (`id`),
  CONSTRAINT `ribbons_ibfk_3` FOREIGN KEY (`coverslip_id`) REFERENCES `coverslips` (`id`),
  CONSTRAINT `ribbons_ibfk_4` FOREIGN KEY (`status`) REFERENCES `ribbonstatuses` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `ribbonstatuses` */

DROP TABLE IF EXISTS `ribbonstatuses`;

CREATE TABLE `ribbonstatuses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` varchar(255) NOT NULL,
  `note` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

/*Table structure for table `sensordata` */

DROP TABLE IF EXISTS `sensordata`;

CREATE TABLE `sensordata` (
  `sensor_id` int(11) DEFAULT NULL,
  `data1` double DEFAULT NULL,
  `data2` double DEFAULT NULL,
  `date_time` datetime DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `settings` */

DROP TABLE IF EXISTS `settings`;

CREATE TABLE `settings` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `label_printer_command` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `species` */

DROP TABLE IF EXISTS `species`;

CREATE TABLE `species` (
  `id` smallint(6) NOT NULL,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `specimens` */

DROP TABLE IF EXISTS `specimens`;

CREATE TABLE `specimens` (
  `case_id` int(11) DEFAULT NULL,
  `specimen_id` int(11) NOT NULL AUTO_INCREMENT,
  `lims_number` int(11) DEFAULT NULL,
  `virus` varchar(255) DEFAULT NULL,
  `age` varchar(255) DEFAULT NULL,
  `death_date` date DEFAULT NULL,
  `brain_region_dissection` varchar(255) DEFAULT NULL,
  `entered_by` int(11) NOT NULL,
  `culture_time` int(11) DEFAULT NULL,
  PRIMARY KEY (`specimen_id`),
  KEY `case_id` (`case_id`),
  KEY `culture_time` (`culture_time`),
  KEY `entered_by` (`entered_by`),
  CONSTRAINT `specimens_ibfk_11` FOREIGN KEY (`case_id`) REFERENCES `case` (`id`),
  CONSTRAINT `specimens_ibfk_12` FOREIGN KEY (`culture_time`) REFERENCES `cultured_time_point` (`id`),
  CONSTRAINT `specimens_ibfk_13` FOREIGN KEY (`entered_by`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=927 DEFAULT CHARSET=utf8;

/*Table structure for table `substitutionprotocols` */

DROP TABLE IF EXISTS `substitutionprotocols`;

CREATE TABLE `substitutionprotocols` (
  `id` smallint(11) NOT NULL AUTO_INCREMENT,
  `protocol` varchar(255) DEFAULT NULL,
  `document_id` int(11) DEFAULT NULL COMMENT 'Reference to documents able',
  PRIMARY KEY (`id`),
  KEY `substitution_ibfk_1` (`document_id`),
  CONSTRAINT `substitutionprotocols_ibfk_1` FOREIGN KEY (`document_id`) REFERENCES `documents` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/*Table structure for table `users` */

DROP TABLE IF EXISTS `users`;

CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(255) NOT NULL,
  `created` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_name` (`user_name`)
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=utf8;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

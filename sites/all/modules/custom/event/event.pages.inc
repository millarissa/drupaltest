<?php


function event_register($form, &$form_state) {

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form for registration on event'),
  );
  // This is the first form element. It's a textfield with a label, "Name"
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
  );
  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#required' => TRUE,
  );
  $form['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of tickets'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

function event_register_submit($form, &$form_state) {

  $record = array(
    'name' => $form_state['values']['name'],
    'last_name' => $form_state['values']['last_name'],
    'number' => $form_state['values']['number'],
  );

  drupal_write_record('event', $record);
  $form_state['redirect'] = 'event/'.$record['nid'];

}

function event_callback($id) {
  $row = db_select('event', 'e')
    ->fields('e', array('name', 'last_name', 'number'))
    ->condition('e.nid', $id)
    ->execute()
    ->fetchAssoc();

  if (empty ($row)) {
    return MENU_NOT_FOUND;
  }

  $output = array();
  $output[] = array(
    '#markup' => t('Name: @name<br>', array('@name'=>$row['name']))
  );
  $output[] = array(
    '#markup' => t('Last name: @last_name<br>', array('@last_name'=>$row['last_name']))
  );
  $output[] = array(
    '#markup' => t('Number: @number<br>', array('@number'=>$row['number']))
  );

  $output[] = module_invoke_all('notice');

  return $output;
}

/**
 * Implements custom hook_notice().
 */

function event_notice() {
  return $output = array(
    '#markup' => t("This is a notice text. It means that hook is working."),
  );
}
